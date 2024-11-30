//
// Created by Anton on 12/1/2024.
//

#ifndef OOP_LAB_6_SRC_UTILS_IELEMENT_H_
#define OOP_LAB_6_SRC_UTILS_IELEMENT_H_

namespace Utils {
    template<class T>
    class IElement {
        public:
            IElement() = default;
            virtual void accept(const T& visitor) = 0;
            virtual ~IElement() = default;
    };

} // Utils

#endif //OOP_LAB_6_SRC_UTILS_IELEMENT_H_
