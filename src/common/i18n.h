// Copyright (c) 2018, Bitlitas
// All rights reserved. Based on Cryptonote and Monero.

#pragma once

#define QT_TRANSLATE_NOOP(context,str) i18n_translate(str,context)

std::string i18n_get_language();
int i18n_set_language(const char *directory, const char *base, std::string language = std::string());
const char *i18n_translate(const char *str, const std::string &context);
static inline std::string get_default_i18n_context() { return std::string(); }
static inline const char *tr(const char *str) { return i18n_translate(str,get_default_i18n_context()); }
