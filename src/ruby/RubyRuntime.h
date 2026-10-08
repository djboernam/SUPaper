#pragma once

#include <QString>
#include <QList>

class RubyRuntime {
public:
    RubyRuntime();
    ~RubyRuntime();

    bool initialize();
    bool loadScript(const QString& path);
    bool executeString(const QString& code);
    QString lastError() const;

private:
    bool initialized_ = false;
    QString last_error_;
};
