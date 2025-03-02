#pragma once

#include <stdint.h>
#include <string.h>
#include <stddef.h>

namespace metareflect
{

/* ========================================================================= */
/* Reflect Macros                                                            */
/* ========================================================================= */

#define ATTRIBUTE_CLASS_NAME "reflect-class;"
#define ATTRIBUTE_PROPERTY_NAME "reflect-property;"
#define ATTRIBUTE_FUNCTION_NAME "reflect-function;"
    
#if METAREFLECT
    #define CLASS(...) class __attribute__((annotate(ATTRIBUTE_CLASS_NAME #__VA_ARGS__)))
    #define UNION(...) union __attribute__((annotate(ATTRIBUTE_CLASS_NAME #__VA_ARGS__)))
    #define PROPERTY(...)  __attribute__((annotate(ATTRIBUTE_PROPERTY_NAME #__VA_ARGS__)))
    #define FUNCTION(...) __attribute__((annotate(ATTRIBUTE_FUNCTION_NAME #__VA_ARGS__)))
    #define META_OBJECT
#else /* else __METAREFLECT__ */
    #define CLASS(...) class
    #define UNION(...) union
    #define PROPERTY(...)
    #define FUNCTION(...)
    #define META_OBJECT \
        friend struct PrimitiveResolver; \
        static constexpr bool IsReflected = true; \
        template<class T> \
        friend constexpr bool AfterSerialize(T *) noexcept; \
        template<class T> \
        friend constexpr bool BeforeSerialize(T *) noexcept; \
        template<class T> \
        friend metareflect::Class const *metareflect::detail::GetClassImpl(metareflect::ClassTag<T>) noexcept;
#endif /* __METAREFLECT__ */


/* ========================================================================= */
/* Traits                                                                    */
/* ========================================================================= */
template<class T>
struct IsSerializable;

template<class T>
struct HasBeforeSerialize;

template<class T>
struct HasAfterSerialize;

template<class T>
struct HasCustomSerialize;

template<class T>
struct HasCustomDump;


/* ========================================================================= */
/* Public API                                                                */
/* ========================================================================= */
class Class;
class Type;
template<class T>
struct TypeTag {};
template<class T>
struct ClassTag {};


template<class T>
Class const *
GetClass() noexcept;

template<class T>
Type const *
GetType() noexcept;


/* ========================================================================= */
/* Serialization                                                             */
/* ========================================================================= */
template<class T, class Serializer>
struct Serialize;


/* ========================================================================= */
/* Helper Functions                                                          */
/* ========================================================================= */
template<class T, class Serializer>
constexpr bool
AfterSerialize(T *_this) noexcept
{
    if constexpr (HasAfterSerialize<T>::value)
        return _this->AfterSerialize();
    return true;
}

template<class T, class Serializer>
constexpr bool
BeforeSerialize(T *_this) noexcept
{
    if constexpr (HasBeforeSerialize<T>::value)
        return _this->BeforeSerialize();
    return true;
}

template<class T, class Serializer>
constexpr bool
CustomSerialize(T *_this) noexcept
{
    if constexpr (HasCustomSerialize<T>::value)
        return _this->Serialize();
    return true;
}

} /* namespace metareflect */

/* ========================================================================= */
/* Detail                                                                    */
/* ========================================================================= */
#include "metareflect_detail.hxx"

