

#pragma once

#include <libdevcore/Exceptions.h>

namespace dev
{
namespace crypto
{
/// Rare malfunction of cryptographic functions.
DEV_SIMPLE_EXCEPTION(CryptoException);
DEV_SIMPLE_EXCEPTION(GmCryptoException);

}  // namespace crypto
}  // namespace dev
