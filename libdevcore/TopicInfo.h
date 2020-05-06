
#pragma once
#include <string>
namespace dev
{
enum TopicStatus
{
    VERIFYING_STATUS = 0,  // init status,for topic which  needs to cert before cert operation has
                           // been finished
    VERIFYI_SUCCESS_STATUS = 1,  // verify success status,for topic which not need to cert or cert
                                 // operation has been finished  with ok result
    VERIFYI_FAILED_STATUS = 2,   // verify failed status, for topic which cert operation has been
                                 // finished with not ok result
};

class TopicItem
{
public:
    std::string topic;
    TopicStatus topicStatus;

public:
    TopicItem() : topicStatus(VERIFYING_STATUS) {}
    bool operator<(const TopicItem& item) const { return this->topic < item.topic; }
};
const std::string topicNeedVerifyPrefix = "#!$TopicNeedVerify_";
const std::string verifyChannelPrefix = "#!$VerifyChannel_";
const std::string pushChannelPrefix = "#!$PushChannel_";
}  // namespace dev
