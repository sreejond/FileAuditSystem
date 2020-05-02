#ifndef FILEAUDITSYSTEMUTIL_H
#define FILEAUDITSYSTEMUTIL_H

#include <array>

static const std::string logFileDir = "/var/log/file_audit_system.log";
static const std::string configurationFile = "/etc/file_audit_system.conf";
static const std::array<std::string, 4> monitorPoints{"timestamp", "pid", "uid", "comm"};

#endif /* FILEAUDITSYSTEMUTIL_H */