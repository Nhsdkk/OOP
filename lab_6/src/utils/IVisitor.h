//
// Created by Anton on 12/1/2024.
//

#ifndef OOP_LAB_6_SRC_UTILS_IVISITOR_H_
#define OOP_LAB_6_SRC_UTILS_IVISITOR_H_
#include "IElement.h"
#include <type_traits>

namespace Utils {
    template<class T1, class T2, class T3, class Base>
    requires (
        std::is_base_of_v<Base, T1> &&
        std::is_base_of_v<Base, T2> &&
        std::is_base_of_v<Base, T3> &&
        std::is_base_of_v<IElement<Base>, Base>
    )
    class IVisitor {
        public:
            IVisitor() = default;
            virtual void visit(const T1& element) = 0;
            virtual void visit(const T2& element) = 0;
            virtual void visit(const T3& element) = 0;
            virtual ~IVisitor() = default;
    };

} // Utils

#endif //OOP_LAB_6_SRC_UTILS_IVISITOR_H_
