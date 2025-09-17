# SIEMonitor

A lightweight Security Information and Event Management (SIEM) platform built in C++ with a Qt6 GUI, designed for real-time log collection, processing, and security monitoring.

## 🏗️ Architecture

SIEMonitor follows a client-server architecture with specialized components for comprehensive security monitoring:

### Server Component
- **Syslog Server**: Receives and processes syslog messages on port 514
- **Client Server**: Handles GUI client connections and data requests
- **Database Layer**: SQLite3-based log storage with multi-threaded writers
- **Command Handler**: Processes client requests for log data and analytics

### Client Component
- **Qt6 GUI Application**: Modern interface with multiple windows (login, connection, SIEM dashboard)
- **Real-time Updates**: Live log monitoring with background worker threads
- **Log Analysis**: Advanced log parsing and filtering capabilities
- **Network Communication**: TCP-based communication with the server

## 📁 Full Project Structure

```
SIEMonitor/
├── server/                              # Server-side SIEM engine
│   ├── src/
│   │   ├── main.cpp                    # Server entry point
│   │   ├── network/
│   │   │   ├── ServerSyslog.h          # Syslog server implementation
│   │   │   ├── ServerClient.h          # Client connection handler
│   │   │   ├── syslog_connections/
│   │   │   │   └── SyslogListener.h    # Syslog message listener
│   │   │   └── clients_connections/
│   │   │       └── ClientListener.h    # GUI client listener
│   │   ├── command_handler/
│   │   │   └── commands/
│   │   │       └── LogsData.hpp        # Log data query commands
│   │   ├── log_parser/
│   │   │   └── LogDatabaseWriter.h     # Database writer with threading
│   │   └── utils/
│   │       ├── ThreadSafeQueue.h       # Thread-safe queue implementation
│   │       ├── ProtocolHandler.h       # Network protocol handling
│   │       └── DBComandExecutor.h      # Database command execution
│   ├── makefile                        # Server build configuration
│   └── target/                         # Build output directory
├── client/                             # Qt6 GUI client application
│   ├── src/
│   │   ├── main.cpp                    # Client entry point
│   │   ├── frontend/
│   │   │   ├── gui.h                   # Main GUI controller
│   │   │   ├── gui.cpp                 # GUI implementation
│   │   │   └── window/
│   │   │       ├── home_screen        
│   │   │       ├── incidents_screen
│   │   │       ├── siem.h              # Main SIEM dashboard
│   │   │       ├── login.hpp           # Login window
│   │   │       ├── siem.h              # Main SIEM dashboard
│   │   │       └── ip_connect.hpp      # Server connection window
│   │   └── backend/
│   │       ├── ServerConnection.h      # Server communication layer
│   │       ├── UpdateWorker.h          # Background update worker
│   │       ├── SplitLogs.hpp           # Log parsing utilities
│   │       ├── SplitLogs.cpp           # Log parsing implementation
│   │       └── Utils.hpp               # Utility functions
│   └── makefile                        # Client build configuration
├── extern                              # External dependencies setup
├── LICENSE                             # GPL-3.0 License
├── .gitignore                         # Git ignore rules
```

## ✨ Key Features

### Real-time Log Processing
- **Syslog Protocol Support**: Standard RFC3164 syslog message reception
- **Multi-threaded Processing**: 4 worker threads for concurrent log writing
- **Thread-safe Queue**: Efficient message queuing between components
- **SQLite3 Storage**: Persistent log storage with optimized queries

### Advanced Log Analysis
- **Severity-based Filtering**: Filter logs by severity levels
- **Host and Source Tracking**: Monitor specific hosts and log sources
- **Time-range Queries**: Historical log analysis with date/time filtering
- **Search Capabilities**: Full-text search across log messages
- **Resolution Tracking**: Mark and track resolved security incidents

### Modern GUI Interface
- **Multi-window Design**: Separate windows for connection, login, and monitoring
- **Real-time Updates**: Live log streaming with automatic refresh
- **Stacked Widget Layout**: Smooth transitions between different views
- **Responsive Design**: Maximized dashboard for comprehensive monitoring

### Network Architecture
- **TCP Communication**: Reliable client-server communication
- **Protocol Handling**: Custom protocol for efficient data exchange
- **Background Processing**: Non-blocking UI with worker threads

## 🔧 Prerequisites

### Server Dependencies
```bash
# Ubuntu/Debian
sudo apt install sqlite3 libsqlite3-dev

# Clone bcrypt library
git clone https://github.com/rg3/bcrypt
```

### Client Dependencies
```bash
# Ubuntu/Debian
sudo apt install qt6-base-dev

# Fedora/RHEL
sudo dnf install qt6-qtbase-devel
```

### Build Requirements
- **C++20 Compiler**: GCC with C++20 support
- **Make**: Build system
- **SQLite3**: Database engine
- **Qt6**: GUI framework
- **bcrypt**: Password hashing library

## 🚀 Installation & Setup

### 1. Clone Repository
```bash
git clone https://github.com/punctIT/SIEMonitor.git
cd SIEMonitor
```

### 2. Install Dependencies
```bash
# Follow extern file instructions
cat extern
```

### 3. Build Server
```bash
cd server
make
```

### 4. Build Client
```bash
cd ../client
make
```

## 📖 Usage

### Starting the Server
```bash
cd server
./target/program
```
The server will:
- Start syslog listener on port 514
- Initialize 4 database writer threads
- Start client connection server
- Begin processing incoming logs

### Launching the Client
```bash
cd client
./target/program
```
The client provides:
1. **Server Connection Window**: Configure server IP and port
2. **Login Window**: User authentication
3. **SIEM Dashboard**: Real-time monitoring and log analysis

### Log Data Queries
The system supports various log queries:
- Get logs by time range
- Filter by severity, host, source
- Search log messages
- Track resolved incidents
- Generate statistics and reports

## 🔒 Security Features

- **Bcrypt Password Hashing**: Secure user authentication
- **SQLite3 Injection Protection**: Parameterized queries
- **Thread-safe Operations**: Concurrent access protection
- **Network Protocol Security**: Custom secure communication protocol

## 📊 Performance

- **Multi-threaded Processing**: Concurrent log writing with 4 worker threads
- **Efficient Queuing**: Thread-safe queue for high-throughput processing
- **Optimized Database**: SQLite3 with indexed queries for fast retrieval
- **Lightweight Design**: Minimal resource footprint

## 📝 License

This project is licensed under the GNU General Public License v3.0 - see the [LICENSE](LICENSE) file for details.

---

**Built with C++20, Qt6, and SQLite3 for enterprise-grade security monitoring**