cmake_minimum_required(VERSION 3.7)

add_compile_options(-Wall -Wextra -Wpedantic)

set(Sources
	DaemonProcess.cpp
	Exception.cpp
	ApplicationStarter.cpp
	MonitorDirectory.cpp
	EventListener.cpp
	Logger.cpp
	EventHandler.cpp
	Parser.cpp
	ConfigurationReader.cpp
)

add_executable(FileAuditSystem ${Sources})

target_link_libraries(FileAuditSystem audit ev)

target_compile_features(FileAuditSystem PRIVATE cxx_uniform_initialization)


install(TARGETS FileAuditSystem RUNTIME DESTINATION /usr/bin)
install(FILES file_audit_system.conf DESTINATION /etc)
install(FILES file-audit-system.service DESTINATION /etc/systemd/system)