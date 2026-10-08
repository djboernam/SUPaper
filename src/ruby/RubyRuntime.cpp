#include "RubyRuntime.h"

RubyRuntime::RubyRuntime() = default;
RubyRuntime::~RubyRuntime() = default;

bool RubyRuntime::initialize() {
    initialized_ = true;
    return true;
}

bool RubyRuntime::loadScript(const QString& path) {
    Q_UNUSED(path);
    return initialized_;
}

bool RubyRuntime::executeString(const QString& code) {
    Q_UNUSED(code);
    return initialized_;
}

QString RubyRuntime::lastError() const {
    return last_error_;
}
