#include "apihandler.h"
#include <coresrv/sl/sl_api.h>
#include <exception>
#include <iostream>
#include <string>

APIHandler::APIHandler(ipc::IFMACActionsReaderPtr fmacReader)
  : m_comExecutor(fmacReader)
{
}

bool
APIHandler::handleAll(const char* method,
                      CivetServer* server,
                      struct mg_connection* conn)
{
  std::string task_ = "";
  std::string command_ = "";
  command_ = GetParam(conn, "command");
  task_ = GetParam(conn, "task");
  if (command_.size() > 0) {
    if (command_ == "start" && task_.size() > 0) {
      try {
        rtl_uint32_t ui_task_ = std::stoul(task_);
        if (m_comExecutor->StartAt(ui_task_)) { // fmac start task
          mg_printf(conn,
                    "HTTP/1.1 200 OK\r\nContent-Type: "
                    "text/html\r\nConnection: close\r\n\r\n");

          mg_printf(conn, "<p>task set to %s</p>", task_.c_str());
          std::cerr << "task set to " << task_ << std::endl;
        } else {
          std::cerr << "task " << task_ << " is not authorized" << std::endl;
          mg_send_http_error(conn, 401, "Task is not authorized");
          return true;
        }
      } catch (std::exception& e) {
        mg_send_http_error(conn, 401, "Wrong task id");
        return true;
      }
    }
  } else {
    mg_printf(conn,
              "HTTP/1.1 200 OK\r\nContent-Type: "
              "text/html\r\nConnection: close\r\n\r\n");
  }
  mg_printf(conn, "</body></html>\n");
  return true;
}

bool
APIHandler::handleGet(CivetServer* server [[maybe_unused]],
                      struct mg_connection* conn)
{
  return handleAll("GET", server, conn);
}

bool
APIHandler::handlePost(CivetServer* server [[maybe_unused]],
                       struct mg_connection* conn)
{
  return handleAll("POST", server, conn);
}

std::string
APIHandler::GetParam(struct mg_connection* conn, const std::string& key) const
{
  const mg_request_info* ri = mg_get_request_info(conn);
  std::string value;
  if (!CivetServer::getParam(ri->query_string, key.c_str(), value)) {
    return "";
  }
  return value;
}
