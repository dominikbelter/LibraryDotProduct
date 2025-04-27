/** @file dotProduct.h
 *
 * DotProduct interface
 *
 * @author Dominik Belter
 */

#ifndef _DOTPRODUCT_H_
#define _DOTPRODUCT_H_

#include <string>
#include <vector>

namespace tutorial {
    /// DotProduct interface
    class DotProduct{
        public:

            /// Dot product type
            enum class Type {
                    /// CPU implementation
                    CPU,
                    /// GPU implementation
                    GPU
            };

            /// overloaded constructor
            DotProduct(const std::string _name, Type _type) : name(_name), type(_type){

            }

            /// Get name of the dot product implementation
            virtual const std::string& getName() const {return name;}

            /// Get implementation type of the dot product
            virtual const Type& getType() const {return type;}

            /// move to goal configuration
            virtual double dotProduct(const std::vector<double>& a, const std::vector<double>& b) = 0;

            /// Virtual descrutor
            virtual ~DotProduct() {}

        protected:
            /// DotProduct type
            Type type;

            /// DotProduct name
            const std::string name;
	};
}

#endif // _DOTPRODUCT_H_
