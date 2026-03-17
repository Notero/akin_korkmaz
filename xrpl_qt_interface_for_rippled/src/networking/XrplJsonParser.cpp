#include "XrplJsonParser.h"

#include <QJsonArray>

namespace {

QString commandToMethodString(RippledCommand command)
{
    // The list mirrors the rippled RPC/WebSocket commands published at
    // https://github.com/XRPLF/rippled/blob/develop/doc/rippled-api.md
    switch (command) {
    case RippledCommand::ACCOUNT_INFO: return QStringLiteral("account_info");
    case RippledCommand::ACCOUNT_CURRENCIES: return QStringLiteral("account_currencies");
    case RippledCommand::ACCOUNT_LINES: return QStringLiteral("account_lines");
    case RippledCommand::ACCOUNT_CHANNELS: return QStringLiteral("account_channels");
    case RippledCommand::ACCOUNT_NFTS: return QStringLiteral("account_nfts");
    case RippledCommand::ACCOUNT_OBJECTS: return QStringLiteral("account_objects");
    case RippledCommand::ACCOUNT_OFFERS: return QStringLiteral("account_offers");
    case RippledCommand::ACCOUNT_TX: return QStringLiteral("account_tx");
    case RippledCommand::AMM_INFO: return QStringLiteral("amm_info");
    case RippledCommand::BOOK_CHANGES: return QStringLiteral("book_changes");
    case RippledCommand::BOOK_OFFERS: return QStringLiteral("book_offers");
    case RippledCommand::GET_AGGREGATE_PRICE: return QStringLiteral("get_aggregate_price");
    case RippledCommand::NFT_BUY_OFFERS: return QStringLiteral("nft_buy_offers");
    case RippledCommand::NFT_SELL_OFFERS: return QStringLiteral("nft_sell_offers");
    case RippledCommand::LEDGER_CLOSED: return QStringLiteral("ledger_closed");
    case RippledCommand::LEDGER_CURRENT: return QStringLiteral("ledger_current");
    case RippledCommand::LEDGER_DATA: return QStringLiteral("ledger_data");
    case RippledCommand::LEDGER_ENTRY: return QStringLiteral("ledger_entry");
    case RippledCommand::LEDGER_HEADER: return QStringLiteral("ledger_header");
    case RippledCommand::PATH_FIND: return QStringLiteral("path_find");
    case RippledCommand::RIPPLE_PATH_FIND: return QStringLiteral("ripple_path_find");
    case RippledCommand::NORIPPLE_CHECK: return QStringLiteral("noripple_check");
    case RippledCommand::TX: return QStringLiteral("tx");
    case RippledCommand::TRANSACTION_ENTRY: return QStringLiteral("transaction_entry");
    case RippledCommand::TX_HISTORY: return QStringLiteral("tx_history");
    case RippledCommand::TX_REDUCE_RELAY: return QStringLiteral("tx_reduce_relay");
    case RippledCommand::SIGN: return QStringLiteral("sign");
    case RippledCommand::SIGN_FOR: return QStringLiteral("sign_for");
    case RippledCommand::SUBMIT: return QStringLiteral("submit");
    case RippledCommand::SUBMIT_MULTISIGNED: return QStringLiteral("submit_multisigned");
    case RippledCommand::SIMULATE: return QStringLiteral("simulate");
    case RippledCommand::CHANNEL_AUTHORIZE: return QStringLiteral("channel_authorize");
    case RippledCommand::CHANNEL_VERIFY: return QStringLiteral("channel_verify");
    case RippledCommand::SERVER_INFO: return QStringLiteral("server_info");
    case RippledCommand::SERVER_STATE: return QStringLiteral("server_state");
    case RippledCommand::SERVER_DEFINITIONS: return QStringLiteral("server_definitions");
    case RippledCommand::FEE: return QStringLiteral("fee");
    case RippledCommand::PING: return QStringLiteral("ping");
    case RippledCommand::RANDOM: return QStringLiteral("random");
    case RippledCommand::MANIFEST: return QStringLiteral("manifest");
    case RippledCommand::GATEWAY_BALANCES: return QStringLiteral("gateway_balances");
    case RippledCommand::DEPOSIT_AUTHORIZED: return QStringLiteral("deposit_authorized");
    case RippledCommand::OWNER_INFO: return QStringLiteral("owner_info");
    case RippledCommand::SUBSCRIBE: return QStringLiteral("subscribe");
    case RippledCommand::UNSUBSCRIBE: return QStringLiteral("unsubscribe");
    case RippledCommand::VAULT_INFO: return QStringLiteral("vault_info");
    case RippledCommand::FEATURE: return QStringLiteral("feature");
    case RippledCommand::VALIDATORS: return QStringLiteral("validators");
    case RippledCommand::VALIDATOR_INFO: return QStringLiteral("validator_info");
    case RippledCommand::VALIDATOR_LIST_SITES: return QStringLiteral("validator_list_sites");
    case RippledCommand::CAN_DELETE: return QStringLiteral("can_delete");
    case RippledCommand::LEDGER_CLEANER: return QStringLiteral("ledger_cleaner");
    case RippledCommand::LEDGER_REQUEST: return QStringLiteral("ledger_request");
    case RippledCommand::LOG_LEVEL: return QStringLiteral("log_level");
    case RippledCommand::LOGROTATE: return QStringLiteral("logrotate");
    case RippledCommand::LEDGER_ACCEPT: return QStringLiteral("ledger_accept");
    case RippledCommand::STOP: return QStringLiteral("stop");
    case RippledCommand::CONNECT: return QStringLiteral("connect");
    case RippledCommand::PEERS: return QStringLiteral("peers");
    case RippledCommand::PEER_RESERVATIONS_ADD: return QStringLiteral("peer_reservations_add");
    case RippledCommand::PEER_RESERVATIONS_DEL: return QStringLiteral("peer_reservations_del");
    case RippledCommand::PEER_RESERVATIONS_LIST: return QStringLiteral("peer_reservations_list");
    case RippledCommand::CONSENSUS_INFO: return QStringLiteral("consensus_info");
    case RippledCommand::FETCH_INFO: return QStringLiteral("fetch_info");
    case RippledCommand::GET_COUNTS: return QStringLiteral("get_counts");
    case RippledCommand::GET_MEMPOOL: return QStringLiteral("get_mempool");
    case RippledCommand::PRINT: return QStringLiteral("print");
    case RippledCommand::UNL_LIST: return QStringLiteral("unl_list");
    case RippledCommand::BLACKLIST: return QStringLiteral("blacklist");
    case RippledCommand::VALIDATION_CREATE: return QStringLiteral("validation_create");
    case RippledCommand::WALLET_PROPOSE: return QStringLiteral("wallet_propose");
    }

    return QStringLiteral("unknown");
}

} // namespace

QJsonDocument XrplJsonParser::buildRequest(const QString &method, const QJsonObject &params)
{
    QJsonObject root;
    root.insert(QStringLiteral("method"), method);

    QJsonObject paramsObj = params;
    if (paramsObj.isEmpty()) {
        paramsObj.insert(QStringLiteral("id"), QStringLiteral("xrplgui"));
    }

    QJsonArray paramsArray;
    paramsArray.append(paramsObj);
    root.insert(QStringLiteral("params"), paramsArray);

    return QJsonDocument(root);
}

QJsonDocument XrplJsonParser::buildRequest(RippledCommand command, const QJsonObject &params)
{
    return buildRequest(commandToMethodString(command), params);
}

std::string XrplJsonParser::commandToString(RippledCommand command)
{
    return commandToMethodString(command).toStdString();
}

