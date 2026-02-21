#ifndef GZ_UTILITY_NOTIFICATION_H
#define GZ_UTILITY_NOTIFICATION_H

#include "dolphin/types.h"

class gzTextBox;

class gzNotification_c {
public:
    enum NotificationType {
        NOTIFY_INFO,
        NOTIFY_WARNING,
        NOTIFY_ERROR
    };

    gzNotification_c();
    gzNotification_c(NotificationType mType);
    ~gzNotification_c();

    void send(const char* message);
    void send(const char* message, NotificationType notification);
    void draw();
    static const int NOTIFICATION_MAX = 5;

private:
    gzTextBox* mpNotifications[NOTIFICATION_MAX];
    int mNumNotifications;
    u32 mStartFrames[NOTIFICATION_MAX];
    NotificationType mTypes[NOTIFICATION_MAX];

    void removeExpired();
};


#endif // GZ_UTILITY_NOTIFICATION_H
