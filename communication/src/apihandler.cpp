#include "apihandler.h"

#include <iostream>
#include <string>

APIHandler::APIHandler()
{}

bool APIHandler::handleAll(const char* method,
                 CivetServer* server,
                 struct mg_connection* conn)
  {
      std::string task_ = "";
      std::string command_ = "";

    mg_printf(conn,
              "HTTP/1.1 200 OK\r\nContent-Type: "
              "text/html\r\nConnection: close\r\n\r\n");
    if (CivetServer::getParam(conn, "command", command_)) {
      if (command_ == "start" && CivetServer::getParam(conn, "task", task_)) {
        if (task_.size() > 0) {
          //packet out_pkt = { me, "fmac", "start", task_ };
          //broker->to_monitor(out_pkt);
          mg_printf(conn, "<p>task set to %s</p>", task_.c_str());
        }
      }
    }
    mg_printf(conn, "</body></html>\n");
    return true;
  }

bool APIHandler::handleGet(CivetServer *server[[maybe_unused]], struct mg_connection *conn)
{
    return handleAll("GET", server, conn);
}

bool APIHandler::handlePost(CivetServer *server[[maybe_unused]], struct mg_connection *conn)
{
    return handleAll("GET", server, conn);
}

std::string
APIHandler::GetParam(struct mg_connection *conn, const std::string &key) const
{
    std::string value;
    if (!CivetServer::getParam(conn, key.c_str(), value))
    {
        return "";
    }
    return value;
}


