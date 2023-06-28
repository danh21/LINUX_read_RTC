# LINUX_read_RTC
    - Reference: https://vimentor.com/vi/lesson/truy-cap-du-lieu-tren-io-module

    - Execute with super user privilege
    - Enter cmd: cat /proc/ioports --> find address port of rtc module to modify code

    - 2 methods:
        + Use system call ioperm or iopl
        + Access through /dev/port