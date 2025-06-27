/**
 * @file    datetimecontroller.h
 * @author  Malhar Sapatnekar
 * @organization Cyient Ltd.
 * @brief   Declaration of the DateTimeController class to manage date and time.
 *
 * The DateTimeController class is responsible for managing the date and time display in the application.
 * It provides functionality to automatically update the date and time every second,
 * and to format the date and time based on user preferences (24-hour or 12-hour format).
 * It also handles the manual setting of date and time.
 */

#ifndef DATETIMEGCONTROLLER_H
#define DATETIMEGCONTROLLER_H

#include <QObject>
#include <QTimer>
#include <QDateTime>
#include <QTimeZone>
#include <QAbstractListModel>
#include <QDebug> // For qDebug(), although typically not in headers for release builds

// Forward declaration of TimeZoneModel if it's a separate class
// #include "timezonemodel.h" // Uncomment and include if TimeZoneModel is in its own header
class TimeZoneModel; // If TimeZoneModel is not in its own header, or to avoid circular dependencies

class DateTimeController : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString date READ date NOTIFY dateChanged)
    Q_PROPERTY(QString time READ time NOTIFY timeChanged)
    Q_PROPERTY(QAbstractListModel* model READ model CONSTANT)
    Q_PROPERTY(QString currentTimeZone READ currentTimeZone NOTIFY timeZoneChanged)

public:
    explicit DateTimeController(QObject *parent = nullptr);
    ~DateTimeController();

    QString date() const;
    QString time() const;
    QAbstractListModel *model() const;
    QString currentTimeZone() const;

    Q_INVOKABLE void setTime(QString dateTime, bool autoTime, bool is24HourFormat, QString timeZoneStr);

signals:
    void dateChanged();
    void timeChanged();
    void timeZoneChanged();

private slots:
    void autoUpdateDateTime();

private:
    QTimer *m_dateTimeTimer;
    QString m_date;
    QString m_time;
    QTimeZone m_timeZone;
    QDateTime m_manualDateTime;
    bool m_autoTime = true;
    bool m_is24HourFormat = true;
    TimeZoneModel *m_timeZoneModel; // Assuming TimeZoneModel is a QAbstractListModel
};

#endif // DATETIMEGCONTROLLER_H
