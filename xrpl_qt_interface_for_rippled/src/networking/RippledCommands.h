#pragma once

// RippledCommands.h
// -----------------------------------------------------------------------------
// Defines the RippledCommand enum and helper utilities for converting between
// string command names and their strongly typed representation. This header is
// intentionally lightweight so it can be included by both the backend and any
// future modules that need to validate user-provided commands.
// -----------------------------------------------------------------------------

#include <stdexcept>
#include <string>

// Comprehensive enumeration of available Rippled API commands. Commands are
// grouped by feature area to keep the list navigable.
enum class RippledCommand
{
    // Account Information Commands
    ACCOUNT_INFO,
    ACCOUNT_CURRENCIES,
    ACCOUNT_LINES,
    ACCOUNT_CHANNELS,
    ACCOUNT_NFTS,
    ACCOUNT_OBJECTS,
    ACCOUNT_OFFERS,
    ACCOUNT_TX,

    // Automated Market Maker (AMM) Commands
    AMM_INFO,

    // Order Book Commands
    BOOK_CHANGES,
    BOOK_OFFERS,
    GET_AGGREGATE_PRICE,

    // NFT Commands
    NFT_BUY_OFFERS,
    NFT_SELL_OFFERS,

    // Ledger Commands
    LEDGER_CLOSED,
    LEDGER_CURRENT,
    LEDGER_DATA,
    LEDGER_ENTRY,
    LEDGER_HEADER,

    // Path Finding Commands
    PATH_FIND,
    RIPPLE_PATH_FIND,
    NORIPPLE_CHECK,

    // Transaction Commands
    TX,
    TRANSACTION_ENTRY,
    TX_HISTORY,
    TX_REDUCE_RELAY,
    SIGN,
    SIGN_FOR,
    SUBMIT,
    SUBMIT_MULTISIGNED,
    SIMULATE,

    // Payment Channel Commands
    CHANNEL_AUTHORIZE,
    CHANNEL_VERIFY,

    // Server/Network Commands
    SERVER_INFO,
    SERVER_STATE,
    SERVER_DEFINITIONS,
    FEE,
    PING,
    RANDOM,
    MANIFEST,

    // Gateway/Balance Commands
    GATEWAY_BALANCES,
    DEPOSIT_AUTHORIZED,
    OWNER_INFO,

    // Subscription Commands
    SUBSCRIBE,
    UNSUBSCRIBE,

    // Vault Command
    VAULT_INFO,

    // Feature/Validator Commands
    FEATURE,
    VALIDATORS,
    VALIDATOR_INFO,
    VALIDATOR_LIST_SITES,

    // Admin Commands
    BLACKLIST,
    CAN_DELETE,
    CONNECT,
    CONSENSUS_INFO,
    FETCH_INFO,
    GET_COUNTS,
    GET_MEMPOOL,
    LEDGER_ACCEPT,
    LEDGER_CLEANER,
    LEDGER_REQUEST,
    LOG_LEVEL,
    LOGROTATE,
    PEERS,
    PEER_RESERVATIONS_ADD,
    PEER_RESERVATIONS_DEL,
    PEER_RESERVATIONS_LIST,
    PRINT,
    STOP,
    UNL_LIST,
    VALIDATION_CREATE,
    WALLET_PROPOSE
};

// Converts a command string (e.g., "server_info") to its corresponding enum
// value. Throws std::runtime_error if the command is not recognized.
RippledCommand stringToCommand(const std::string& cmd);
