#ifndef _CAPP_H
#define _CAPP_H

enum app_t
{
    app__begin,
    app_none,
    app_null,
    app_pipe,
    app_range,
    app_take,
    app_last,
    app__end
};

class CApp
{
public:
    CApp();
    virtual ~CApp();

    static std::shared_ptr<CApp> create(app_t type);
    static app_t get_type_by_name(const std::string &name);

    int set_arg(std::vector<std::string> arg);
    virtual int init() = 0;

    void set_inner_app(std::shared_ptr<CApp> app);

    std::string get_err() const;

    virtual bool available() const = 0;
    virtual char next() = 0;

protected:
    std::vector<std::string> args;
    std::string error;
    std::shared_ptr<CApp> inner;
};

// --------------------------------------------------

class CAppNull : public CApp
{
public:
    int init() override;
    bool available() const override;
    char next() override;
};

class CAppPipe : public CApp
{
public:
    int init() override;
    bool available() const override;
    char next() override;
};

class CAppRange : public CApp
{
public:
    int init() override;
    bool available() const override;
    char next() override;

private:
    int start, end;
    bool infinite;
    std::queue<char> data;
};

class CAppTake : public CApp
{
public:
    int init() override;
    bool available() const override;
    char next() override;

private:
    int start, end;
    std::queue<char> data;
};

class CAppLast : public CApp
{
public:
    int init() override;
    bool available() const override;
    char next() override;

private:
    int start, end;
    std::queue<std::queue<char>> data;
};

#endif