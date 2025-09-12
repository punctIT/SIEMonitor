#pragma once
#include <string>
#include "../../utils/ProtocolHandler.h"
#include "../../utils/DBComandExecutor.h"

class UpdateLogsData: ProtocolHandler{
    DBComandExecutor logs_db;
public:
    UpdateLogsData();
    UpdateLogsData& update_resolved(const std::string id,const std::string status);

};