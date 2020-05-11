


#include "MPTStateFactory.h"
using namespace dev;
using namespace dev::mptstate;
using namespace dev::eth;
using namespace dev::executive;

std::shared_ptr<StateFace> MPTStateFactory::getState(
    h256 const& _root, std::shared_ptr<dev::storage::TableFactory>)
{
    if (_root == dev::h256())
    {
        auto mptState = std::make_shared<MPTState>(m_accountStartNonce, m_db, BaseState::Empty);

        return mptState;
    }
    else
    {
        auto mptState =
            std::make_shared<MPTState>(m_accountStartNonce, m_db, BaseState::PreExisting);
        mptState->setRoot(_root);

        return mptState;
    }
}
