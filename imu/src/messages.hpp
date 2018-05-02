
/*
 * THIS IS AN AUTO-GENERATED FILE. DO NOT MODIFY AS CHANGES MIGHT BE OVERWRITTEN!
 */

#ifndef VISITABLE_TYPE_TRAIT
#define VISITABLE_TYPE_TRAIT
#include <cstdint>
#include <string>
#include <utility>

template<bool b>
struct visitorSelector {
    template<typename T, class Visitor>
    static void impl(uint32_t fieldIdentifier, std::string &&typeName, std::string &&name, T &value, Visitor &visitor) {
        visitor.visit(fieldIdentifier, std::move(typeName), std::move(name), value);
    }
};

template<>
struct visitorSelector<true> {
    template<typename T, class Visitor>
    static void impl(uint32_t fieldIdentifier, std::string &&typeName, std::string &&name, T &value, Visitor &visitor) {
        visitor.visit(fieldIdentifier, std::move(typeName), std::move(name), value);
    }
};

template<typename T>
struct isVisitable {
    static const bool value = false;
};

template<typename T, class Visitor>
void doVisit(uint32_t fieldIdentifier, std::string &&typeName, std::string &&name, T &value, Visitor &visitor) {
    visitorSelector<isVisitable<T>::value >::impl(fieldIdentifier, std::move(typeName), std::move(name), value, visitor);
}
#endif

#ifndef TRIPLET_FORWARD_VISITABLE_TYPE_TRAIT
#define TRIPLET_FORWARD_VISITABLE_TYPE_TRAIT
#include <cstdint>
#include <string>
#include <utility>

template<bool b>
struct tripletForwardVisitorSelector {
    template<typename T, class PreVisitor, class Visitor, class PostVisitor>
    static void impl(uint32_t fieldIdentifier, std::string &&typeName, std::string &&name, T &value, PreVisitor &&preVisit, Visitor &&visit, PostVisitor &&postVisit) {
        (void)preVisit;
        (void)postVisit;
        std::forward<Visitor>(visit)(fieldIdentifier, std::move(typeName), std::move(name), value);
    }
};

template<>
struct tripletForwardVisitorSelector<true> {
    template<typename T, class PreVisitor, class Visitor, class PostVisitor>
    static void impl(uint32_t fieldIdentifier, std::string &&typeName, std::string &&name, T &value, PreVisitor &&preVisit, Visitor &&visit, PostVisitor &&postVisit) {
        (void)fieldIdentifier;
        (void)typeName;
        (void)name;
        // Apply preVisit, visit, and postVisit on value.
        value.accept(preVisit, visit, postVisit);
    }
};

template<typename T>
struct isTripletForwardVisitable {
    static const bool value = false;
};

template< typename T, class PreVisitor, class Visitor, class PostVisitor>
void doTripletForwardVisit(uint32_t fieldIdentifier, std::string &&typeName, std::string &&name, T &value, PreVisitor &&preVisit, Visitor &&visit, PostVisitor &&postVisit) {
    tripletForwardVisitorSelector<isTripletForwardVisitable<T>::value >::impl(fieldIdentifier, std::move(typeName), std::move(name), value, std::move(preVisit), std::move(visit), std::move(postVisit)); // NOLINT
}
#endif


#ifndef ACCELEROMETERVALUES_HPP
#define ACCELEROMETERVALUES_HPP

#ifdef WIN32
    // Export symbols if compile flags "LIB_SHARED" and "LIB_EXPORTS" are set on Windows.
    #ifdef LIB_SHARED
        #ifdef LIB_EXPORTS
            #define LIB_API __declspec(dllexport)
        #else
            #define LIB_API __declspec(dllimport)
        #endif
    #else
        // Disable definition if linking statically.
        #define LIB_API
    #endif
#else
    // Disable definition for non-Win32 systems.
    #define LIB_API
#endif

#include <string>
#include <utility>

using namespace std::string_literals; // NOLINT
class LIB_API accelerometerValues {
    public:
        accelerometerValues() = default;
        accelerometerValues(const accelerometerValues&) = default;
        accelerometerValues& operator=(const accelerometerValues&) = default;
        accelerometerValues(accelerometerValues&&) noexcept = default; // NOLINT
        accelerometerValues& operator=(accelerometerValues&&) noexcept = default; // NOLINT
        ~accelerometerValues() = default;

    public:
        static int32_t ID();
        static const std::string ShortName();
        static const std::string LongName();
        
        accelerometerValues& acceldata0(const float &v) noexcept;
        float acceldata0() const noexcept;
        
        accelerometerValues& acceldata1(const float &v) noexcept;
        float acceldata1() const noexcept;
        
        accelerometerValues& acceldata2(const float &v) noexcept;
        float acceldata2() const noexcept;
        

        template<class Visitor>
        void accept(Visitor &visitor) {
            visitor.preVisit(ID(), ShortName(), LongName());
            
            doVisit(1, std::move("float"s), std::move("acceldata0"s), m_acceldata0, visitor);
            
            doVisit(2, std::move("float"s), std::move("acceldata1"s), m_acceldata1, visitor);
            
            doVisit(3, std::move("float"s), std::move("acceldata2"s), m_acceldata2, visitor);
            
            visitor.postVisit();
        }

        template<class PreVisitor, class Visitor, class PostVisitor>
        void accept(PreVisitor &&preVisit, Visitor &&visit, PostVisitor &&postVisit) {
            std::forward<PreVisitor>(preVisit)(ID(), ShortName(), LongName());
            
            doTripletForwardVisit(1, std::move("float"s), std::move("acceldata0"s), m_acceldata0, preVisit, visit, postVisit);
            
            doTripletForwardVisit(2, std::move("float"s), std::move("acceldata1"s), m_acceldata1, preVisit, visit, postVisit);
            
            doTripletForwardVisit(3, std::move("float"s), std::move("acceldata2"s), m_acceldata2, preVisit, visit, postVisit);
            
            std::forward<PostVisitor>(postVisit)();
        }

    private:
        
        float m_acceldata0{ 0.0f }; // field identifier = 1.
        
        float m_acceldata1{ 0.0f }; // field identifier = 2.
        
        float m_acceldata2{ 0.0f }; // field identifier = 3.
        
};


template<>
struct isVisitable<accelerometerValues> {
    static const bool value = true;
};
template<>
struct isTripletForwardVisitable<accelerometerValues> {
    static const bool value = true;
};
#endif


/*
 * THIS IS AN AUTO-GENERATED FILE. DO NOT MODIFY AS CHANGES MIGHT BE OVERWRITTEN!
 */

#ifndef VISITABLE_TYPE_TRAIT
#define VISITABLE_TYPE_TRAIT
#include <cstdint>
#include <string>
#include <utility>

template<bool b>
struct visitorSelector {
    template<typename T, class Visitor>
    static void impl(uint32_t fieldIdentifier, std::string &&typeName, std::string &&name, T &value, Visitor &visitor) {
        visitor.visit(fieldIdentifier, std::move(typeName), std::move(name), value);
    }
};

template<>
struct visitorSelector<true> {
    template<typename T, class Visitor>
    static void impl(uint32_t fieldIdentifier, std::string &&typeName, std::string &&name, T &value, Visitor &visitor) {
        visitor.visit(fieldIdentifier, std::move(typeName), std::move(name), value);
    }
};

template<typename T>
struct isVisitable {
    static const bool value = false;
};

template<typename T, class Visitor>
void doVisit(uint32_t fieldIdentifier, std::string &&typeName, std::string &&name, T &value, Visitor &visitor) {
    visitorSelector<isVisitable<T>::value >::impl(fieldIdentifier, std::move(typeName), std::move(name), value, visitor);
}
#endif

#ifndef TRIPLET_FORWARD_VISITABLE_TYPE_TRAIT
#define TRIPLET_FORWARD_VISITABLE_TYPE_TRAIT
#include <cstdint>
#include <string>
#include <utility>

template<bool b>
struct tripletForwardVisitorSelector {
    template<typename T, class PreVisitor, class Visitor, class PostVisitor>
    static void impl(uint32_t fieldIdentifier, std::string &&typeName, std::string &&name, T &value, PreVisitor &&preVisit, Visitor &&visit, PostVisitor &&postVisit) {
        (void)preVisit;
        (void)postVisit;
        std::forward<Visitor>(visit)(fieldIdentifier, std::move(typeName), std::move(name), value);
    }
};

template<>
struct tripletForwardVisitorSelector<true> {
    template<typename T, class PreVisitor, class Visitor, class PostVisitor>
    static void impl(uint32_t fieldIdentifier, std::string &&typeName, std::string &&name, T &value, PreVisitor &&preVisit, Visitor &&visit, PostVisitor &&postVisit) {
        (void)fieldIdentifier;
        (void)typeName;
        (void)name;
        // Apply preVisit, visit, and postVisit on value.
        value.accept(preVisit, visit, postVisit);
    }
};

template<typename T>
struct isTripletForwardVisitable {
    static const bool value = false;
};

template< typename T, class PreVisitor, class Visitor, class PostVisitor>
void doTripletForwardVisit(uint32_t fieldIdentifier, std::string &&typeName, std::string &&name, T &value, PreVisitor &&preVisit, Visitor &&visit, PostVisitor &&postVisit) {
    tripletForwardVisitorSelector<isTripletForwardVisitable<T>::value >::impl(fieldIdentifier, std::move(typeName), std::move(name), value, std::move(preVisit), std::move(visit), std::move(postVisit)); // NOLINT
}
#endif


#ifndef GYROSCOPEVALUES_HPP
#define GYROSCOPEVALUES_HPP

#ifdef WIN32
    // Export symbols if compile flags "LIB_SHARED" and "LIB_EXPORTS" are set on Windows.
    #ifdef LIB_SHARED
        #ifdef LIB_EXPORTS
            #define LIB_API __declspec(dllexport)
        #else
            #define LIB_API __declspec(dllimport)
        #endif
    #else
        // Disable definition if linking statically.
        #define LIB_API
    #endif
#else
    // Disable definition for non-Win32 systems.
    #define LIB_API
#endif

#include <string>
#include <utility>

using namespace std::string_literals; // NOLINT
class LIB_API gyroscopeValues {
    public:
        gyroscopeValues() = default;
        gyroscopeValues(const gyroscopeValues&) = default;
        gyroscopeValues& operator=(const gyroscopeValues&) = default;
        gyroscopeValues(gyroscopeValues&&) noexcept = default; // NOLINT
        gyroscopeValues& operator=(gyroscopeValues&&) noexcept = default; // NOLINT
        ~gyroscopeValues() = default;

    public:
        static int32_t ID();
        static const std::string ShortName();
        static const std::string LongName();
        
        gyroscopeValues& gyrodata0(const float &v) noexcept;
        float gyrodata0() const noexcept;
        
        gyroscopeValues& gyrodata1(const float &v) noexcept;
        float gyrodata1() const noexcept;
        
        gyroscopeValues& gyrodata2(const float &v) noexcept;
        float gyrodata2() const noexcept;
        

        template<class Visitor>
        void accept(Visitor &visitor) {
            visitor.preVisit(ID(), ShortName(), LongName());
            
            doVisit(1, std::move("float"s), std::move("gyrodata0"s), m_gyrodata0, visitor);
            
            doVisit(2, std::move("float"s), std::move("gyrodata1"s), m_gyrodata1, visitor);
            
            doVisit(3, std::move("float"s), std::move("gyrodata2"s), m_gyrodata2, visitor);
            
            visitor.postVisit();
        }

        template<class PreVisitor, class Visitor, class PostVisitor>
        void accept(PreVisitor &&preVisit, Visitor &&visit, PostVisitor &&postVisit) {
            std::forward<PreVisitor>(preVisit)(ID(), ShortName(), LongName());
            
            doTripletForwardVisit(1, std::move("float"s), std::move("gyrodata0"s), m_gyrodata0, preVisit, visit, postVisit);
            
            doTripletForwardVisit(2, std::move("float"s), std::move("gyrodata1"s), m_gyrodata1, preVisit, visit, postVisit);
            
            doTripletForwardVisit(3, std::move("float"s), std::move("gyrodata2"s), m_gyrodata2, preVisit, visit, postVisit);
            
            std::forward<PostVisitor>(postVisit)();
        }

    private:
        
        float m_gyrodata0{ 0.0f }; // field identifier = 1.
        
        float m_gyrodata1{ 0.0f }; // field identifier = 2.
        
        float m_gyrodata2{ 0.0f }; // field identifier = 3.
        
};


template<>
struct isVisitable<gyroscopeValues> {
    static const bool value = true;
};
template<>
struct isTripletForwardVisitable<gyroscopeValues> {
    static const bool value = true;
};
#endif

