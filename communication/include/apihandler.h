#pragma once

#include "i_fmacactionsreader.h"
#include <CivetServer.h>

class APIHandler : public CivetHandler
{
public:
  APIHandler(ipc::IFMACActionsReaderPtr fmacReader);
  ~APIHandler() override = default;

  bool handleGet(CivetServer* server, struct mg_connection* conn) override;
  bool handlePost(CivetServer* server, struct mg_connection* conn) override;

private:
  std::string GetParam(struct mg_connection* conn,
                       const std::string& key) const;

private:
  bool handleAll(const char* method,
                 CivetServer* server,
                 struct mg_connection* conn);
  ipc::IFMACActionsReaderPtr m_comExecutor;
};
