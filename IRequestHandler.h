#pragma once

class IRequestHandler
{
public:
    virtual ~IRequestHandler() = default;
};

class LoginRequestHandler : public IRequestHandler {
public:
    LoginRequestHandler() = default;
    ~LoginRequestHandler() override = default;
};
