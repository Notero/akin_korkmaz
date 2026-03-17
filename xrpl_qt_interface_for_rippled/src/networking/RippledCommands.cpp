// RippledCommands.cpp
// -----------------------------------------------------------------------------
// Implements helper functions for working with RippledCommand values, including
// a validated string-to-enum conversion used by the backend when handling user
// input.
// -----------------------------------------------------------------------------

#include "RippledCommands.h"

#include <unordered_map>

RippledCommand stringToCommand(const std::string& cmd)
{
    static const std::unordered_map<std::string, RippledCommand> commandMap = {
        // Account commands
        {"account_info", RippledCommand::ACCOUNT_INFO},
        {"account_currencies", RippledCommand::ACCOUNT_CURRENCIES},
        {"account_lines", RippledCommand::ACCOUNT_LINES},
        {"account_channels", RippledCommand::ACCOUNT_CHANNELS},
        {"account_nfts", RippledCommand::ACCOUNT_NFTS},
        {"account_objects", RippledCommand::ACCOUNT_OBJECTS},
        {"account_offers", RippledCommand::ACCOUNT_OFFERS},
        {"account_tx", RippledCommand::ACCOUNT_TX},

        // AMM commands
        {"amm_info", RippledCommand::AMM_INFO},

        // Order book commands
        {"book_changes", RippledCommand::BOOK_CHANGES},
        {"book_offers", RippledCommand::BOOK_OFFERS},
        {"get_aggregate_price", RippledCommand::GET_AGGREGATE_PRICE},

        // NFT commands
        {"nft_buy_offers", RippledCommand::NFT_BUY_OFFERS},
        {"nft_sell_offers", RippledCommand::NFT_SELL_OFFERS},

        // Ledger commands
        {"ledger_closed", RippledCommand::LEDGER_CLOSED},
        {"ledger_current", RippledCommand::LEDGER_CURRENT},
        {"ledger_data", RippledCommand::LEDGER_DATA},
        {"ledger_entry", RippledCommand::LEDGER_ENTRY},
        {"ledger_header", RippledCommand::LEDGER_HEADER},

        // Path finding commands
        {"path_find", RippledCommand::PATH_FIND},
        {"ripple_path_find", RippledCommand::RIPPLE_PATH_FIND},
        {"noripple_check", RippledCommand::NORIPPLE_CHECK},

        // Transaction commands
        {"tx", RippledCommand::TX},
        {"transaction_entry", RippledCommand::TRANSACTION_ENTRY},
        {"tx_history", RippledCommand::TX_HISTORY},
        {"tx_reduce_relay", RippledCommand::TX_REDUCE_RELAY},
        {"sign", RippledCommand::SIGN},
        {"sign_for", RippledCommand::SIGN_FOR},
        {"submit", RippledCommand::SUBMIT},
        {"submit_multisigned", RippledCommand::SUBMIT_MULTISIGNED},
        {"simulate", RippledCommand::SIMULATE},

        // Payment channel commands
        {"channel_authorize", RippledCommand::CHANNEL_AUTHORIZE},
        {"channel_verify", RippledCommand::CHANNEL_VERIFY},

        // Server/network commands
        {"server_info", RippledCommand::SERVER_INFO},
        {"server_state", RippledCommand::SERVER_STATE},
        {"server_definitions", RippledCommand::SERVER_DEFINITIONS},
        {"fee", RippledCommand::FEE},
        {"ping", RippledCommand::PING},
        {"random", RippledCommand::RANDOM},
        {"manifest", RippledCommand::MANIFEST},

        // Gateway/balance commands
        {"gateway_balances", RippledCommand::GATEWAY_BALANCES},
        {"deposit_authorized", RippledCommand::DEPOSIT_AUTHORIZED},
        {"owner_info", RippledCommand::OWNER_INFO},

        // Subscription commands
        {"subscribe", RippledCommand::SUBSCRIBE},
        {"unsubscribe", RippledCommand::UNSUBSCRIBE},

        // Vault command
        {"vault_info", RippledCommand::VAULT_INFO},

        // Feature/validator commands
        {"feature", RippledCommand::FEATURE},
        {"validators", RippledCommand::VALIDATORS},
        {"validator_info", RippledCommand::VALIDATOR_INFO},
        {"validator_list_sites", RippledCommand::VALIDATOR_LIST_SITES},

        // Admin commands
        {"blacklist", RippledCommand::BLACKLIST},
        {"can_delete", RippledCommand::CAN_DELETE},
        {"connect", RippledCommand::CONNECT},
        {"consensus_info", RippledCommand::CONSENSUS_INFO},
        {"fetch_info", RippledCommand::FETCH_INFO},
        {"get_counts", RippledCommand::GET_COUNTS},
        {"get_mempool", RippledCommand::GET_MEMPOOL},
        {"ledger_accept", RippledCommand::LEDGER_ACCEPT},
        {"ledger_cleaner", RippledCommand::LEDGER_CLEANER},
        {"ledger_request", RippledCommand::LEDGER_REQUEST},
        {"log_level", RippledCommand::LOG_LEVEL},
        {"logrotate", RippledCommand::LOGROTATE},
        {"peers", RippledCommand::PEERS},
        {"peer_reservations_add", RippledCommand::PEER_RESERVATIONS_ADD},
        {"peer_reservations_del", RippledCommand::PEER_RESERVATIONS_DEL},
        {"peer_reservations_list", RippledCommand::PEER_RESERVATIONS_LIST},
        {"print", RippledCommand::PRINT},
        {"stop", RippledCommand::STOP},
        {"unl_list", RippledCommand::UNL_LIST},
        {"validation_create", RippledCommand::VALIDATION_CREATE},
        {"wallet_propose", RippledCommand::WALLET_PROPOSE}
    };

    auto it = commandMap.find(cmd);
    if (it == commandMap.end()) {
        throw std::runtime_error("Unknown rippled command: " + cmd);
    }

    return it->second;
}

