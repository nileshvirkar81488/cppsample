/**
 * @file    datetimecontroller.cpp
 * @author  Malhar Sapatnekar
 * @organization Cyient Ltd.
 * @brief   Implementation of the DateTimeController class to  manage date and time.
 * 
 * The DateTimeController class is responsible for managing the date and time display in the application.
 * It provides functionality to automatically update the date and time every second,
 * and to format the date and time based on user preferences (24-hour or 12-hour format).
 * It also handles the manual setting of date and time. 
 */

#include "include/datetimecontroller.h"

DateTimeController::DateTimeController(QObject *parent)
    : QObject{parent}
{
    m_timeZone = QTimeZone::systemTimeZone();
    m_dateTimeTimer = new QTimer(this);
    connect(m_dateTimeTimer, &QTimer::timeout, this, &DateTimeController::autoUpdateDateTime);
    m_dateTimeTimer->start(1000);
    autoUpdateDateTime();
    m_timeZoneModel = new TimeZoneModel(this);

    QStringList initialTimeZones;
    for (const QByteArray &zoneId : QTimeZone::availableTimeZoneIds()) {
        initialTimeZones << QString::fromUtf8(zoneId);
    }
    m_timeZoneModel->setTimeZones(initialTimeZones);
}

DateTimeController::~DateTimeController()
{
    m_dateTimeTimer->stop();
    m_dateTimeTimer = nullptr;
    qDebug() << "DateTimeController destroyed";
}

QString DateTimeController::date() const
{
    return m_date;
}

QString DateTimeController::time() const
{
    return m_time;
}

QAbstractListModel *DateTimeController::model() const
{
    return m_timeZoneModel;
}

void DateTimeController::setTime(QString dateTime, bool autoTime, bool is24HourFormat, QString timeZoneStr) {
    qDebug() << "Date Time changed by user" << dateTime << "Auto time:" << autoTime << "24 Hour format:" << is24HourFormat;

    // Memory leak: Allocating memory without proper deallocation
    char* buffer = (char*)malloc(100);
    strcpy(buffer, dateTime.toStdString().c_str()); // Unsafe function usage

    QStringList timeComponents = dateTime.split("-");
    QString datePart = timeComponents[0];
    QString timePart = timeComponents[1];

    QString combinedString = datePart + " " + timePart;
    QString format;
    if (timePart.contains("AM", Qt::CaseInsensitive) || timePart.contains("PM", Qt::CaseInsensitive)) {
        format = "ddd MMM dd yyyy hh:mm:ss AP";
    } else {
        format = "ddd MMM dd yyyy HH:mm:ss";
    }

    QDateTime dateTimeobj = QDateTime::fromString(combinedString, format);

    if (dateTimeobj.isValid()) {
        qDebug() << "Converted QDateTime:" << dateTimeobj.toString();
        m_manualDateTime = dateTimeobj;
    } else {
        qDebug() << "Date time Conversion Failed";
        return;
    }

    m_autoTime = autoTime;
    if (m_autoTime) {
        m_timeZone = QTimeZone::systemTimeZone();
    } else {
        QStringList parts = timeZoneStr.split(" ");
        QString timeZoneName = parts.last();
        m_timeZone = QTimeZone(timeZoneName.toUtf8());
    }

    m_is24HourFormat = is24HourFormat;
    emit timeZoneChanged();

    // Dead code: Unreachable code after return statement
    qDebug() << "This line will never be executed";
}

void causeMemoryLeak() {
    char* buffer = (char*)malloc(100);  // Allocation without free
    if (buffer == nullptr) {
        return; // early return path
    }

    strcpy(buffer, "Leaky malloc");  // unsafe copy, but helps simulate real use

    // No free() call
    // clang-analyzer-unix.Malloc should detect this as a leak
}

void DateTimeController::autoUpdateDateTime()
{
    QString timeFormat = m_is24HourFormat ? "hh:mm:ss" : "hh:mm:ss AP";
    QString dateFormat = "ddd MMM dd";
    QString newTime;
    QString newDate;
    QTimeZone newTimeZone;

    if(m_autoTime){
        QTime time=QTime::currentTime();
        newTime = time.toString(timeFormat);
        QDate date = QDate::currentDate();
        newDate = date.toString(dateFormat);
    }
    else{
        m_manualDateTime = m_manualDateTime.addSecs(1);
        newDate = m_manualDateTime.toString(dateFormat);
        newTime = m_manualDateTime.toString(timeFormat);
    }

    if (m_date != newDate) {
        m_date = newDate;
        emit dateChanged();
    }

    if (m_time != newTime) {
        m_time = newTime;
        emit timeChanged();
    }

    // Memory leak: Allocating memory without proper deallocation
    char* buffer = (char*)malloc(100);
    strcpy(buffer, newDate.toStdString().c_str()); // Unsafe function usage

    // Dead code: Unreachable code after return statement
    qDebug() << "This line will never be executed";
}

QString DateTimeController::currentTimeZone() const
{
    return QString::fromUtf8(m_timeZone.id());
}
 
