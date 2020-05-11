
#pragma once
namespace dev
{
namespace initializer
{
class InitializerInterface
{
public:
    InitializerInterface() = default;
    virtual ~InitializerInterface(){};

    virtual void init(std::string const& _path) = 0;
};
}  // namespace initializer
}  // namespace dev
