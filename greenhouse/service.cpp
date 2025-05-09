#include "service.hh"

float roundToTenths(float value) {
  return (round(value * 10.0) / 10.0);
}

String formatDate(String inputDate) {
  // Разделить строку по символу '/'
  int firstSlash = inputDate.indexOf('/');
  int secondSlash = inputDate.lastIndexOf('/');

  if (firstSlash == -1 || secondSlash == -1) {
    return "Invalid date format";
  }

  // Извлечь месяц, день и год
  String month = inputDate.substring(0, firstSlash);
  String day = inputDate.substring(firstSlash + 1, secondSlash);
  String year = inputDate.substring(secondSlash + 1);

  // Проверить, что длина каждого компонента корректная
  if (month.length() != 2 || day.length() != 2 || year.length() != 4) {
    return "Invalid date format";
  }

  // Сформировать новую строку в формате YYYY-MM-DD
  String formattedDate = year + "-" + month + "-" + day;
  return formattedDate;
}

String formatIsoToShort(String isoformat) {
  // Извлекаем нужные части
  String datePart = isoformat.substring(0, 10);  // "YYYY-MM-DD"
  String timePart = isoformat.substring(11, 16); // "HH:MM"

  return datePart + " " + timePart;
}

String getDataTimeFromJson(String input) {
    DynamicJsonDocument json(1024);

    deserializeJson(json, input);

    String output = formatIsoToShort(json["current_time"].as<String>());

    // String date = formatDate(json["date"].as<String>());

    // output += String(MSG_DATE) + ": ";
    // output += date;
    // output += " " + json["time"].as<String>() + "\n";
    return output;
}

/*
Регулярное выражение для проверки формата "Date: yyyy-MM-dd HH:mm"
yyyy: 4 цифры
MM: 2 цифры от 01 до 12
dd: 2 цифры от 01 до 31
HH: 2 цифры от 00 до 23
mm: 2 цифры от 00 до 59
*/
bool isCorrectDateFormat(String dateTime){
    // Создание изменяемого массива char, достаточно большого для хранения строки
    char charArray[dateTime.length() + 1];

    // Копирование строки в массив char
    dateTime.toCharArray(charArray, dateTime.length() + 1);
  
    // Создание объекта для хранения результата
    MatchState ms;
    ms.Target(charArray);

    // Проверка строки на соответствие регулярному выражению
    char result = ms.Match((String(MSG_DATE) + ": (20%d%d)-([01]%d)-([0-3]%d) ([0-2]%d):([0-5]%d)").c_str());

    if (result == REGEXP_MATCHED)
        return true;    //  String matches the format!
    return false;       //  String does not match the format.
}
