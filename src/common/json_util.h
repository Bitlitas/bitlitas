// Copyright (c) 2018, Bitlitas
// All rights reserved. Based on Cryptonote and Monero.

#pragma once 

#define GET_FIELD_FROM_JSON_RETURN_ON_ERROR(json, name, type, jtype, mandatory, def) \
  type field_##name = def; \
  bool field_##name##_found = false; \
  (void)field_##name##_found; \
  do if (json.HasMember(#name)) \
  { \
    if (json[#name].Is##jtype()) \
    { \
      field_##name = json[#name].Get##jtype(); \
      field_##name##_found = true; \
    } \
    else \
    { \
      LOG_ERROR("Field " << #name << " found in JSON, but not " << #jtype); \
      return false; \
    } \
  } \
  else if (mandatory) \
  { \
    LOG_ERROR("Field " << #name << " not found in JSON"); \
    return false; \
  } while(0)

