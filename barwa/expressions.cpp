#include "script.h"

namespace barwa {
    inline std::string script::force_string( const char c ) {
        std::string result( "" );
        result += c;
        return result;
    }

    const inline bool script::is_operator( const std::string& o ) {
        return (o == "+" || o == "-" || o == "*" || o == "/" || o == "^" || o == "==" || o == "!=" || o == ">=" || o == ">" || o == "<=" || o == "<");
    }
	
	const inline int_fast8_t script::precedence( const std::string& o ) {
		if ( o == "+" || o == "-" )
			return 1;
		if ( o == "*" || o == "/" )
			return 2;
		if ( o == "^" )
			return 3;
        return 0;
	}

    const inline long double script::apply_operation( const long double a, const long double b, const std::string& o ) {
        if ( o == "+" )
            return a + b;
        if ( o == "-" )
            return a - b;
        if ( o == "/" )
            if ( b == 0 ) return NAN;
            else          return a / b;
        if ( o == "*" )
            return a * b;
        if ( o == "^" )
            return pow( a, b );
        if ( o == "==" )
            return a == b;
        if ( o == "!=" )
            return a != b;
        if ( o == ">=" )
            return a >= b;
        if ( o == ">" )
            return a > b;
        if ( o == "<=" )
            return a <= b;
        if ( o == "<" )
            return a < b;
        return NAN;
    }

    /*
        This code detokenizes the expression
        and swaps variable names with values
    */
    std::string script::preprocess_expression( vars& variables, std::vector<std::string*>& tokens ) {
        std::string expression( "" );
        bool found( false );
        
        // searching for variable names
        for ( std::string* t : tokens ) {
            found = false;
            for ( auto& pair : variables ) {
                // if we found the variable, we replace it with real content
                if ( *t == pair.first ) {
                    found = true;
                    expression += *pair.second + " ";
                    break;
                }
            }
            
            // exit from both loops
            if ( found ) continue;

            // appending the tokens
            expression += *t + " ";
        }

        return expression;
    }

    /*
        This code evaluates expressions both
        mathematical and conditional
    */
    long double script::evaluate( const std::string& expression ) {
        std::stack<std::string> operators;
        std::stack<long double> operands;
        long double operand, a, b;
        std::string o, op1, op2;
        // handler of leading negative numbers
        bool negative( true );

        // restructurizing the expression into RPN
        for ( size_t i = 0; i < expression.length(); ++i ) {
            if ( expression[i] == ' ' )
                continue;

            // trick for the operators
            op1 = force_string( expression[i] );
            if ( i + 1 < expression.length() )
                op2 = force_string( expression[i] ) + force_string( expression[i + 1] );
            else
                op2 = op1;

            // parsing numbers (both floating points and negative)
            if ( isdigit( expression[i] ) || (expression[i] == '-' && negative && i + 1 < expression.length() && isdigit(expression[i + 1])) ) {
                std::stringstream ss;
                if ( expression[i] == '-' ) {
                    ss << '-';
                    i++;
                }
                while ( i < expression.length() && (isdigit( expression[i] ) || expression[i] == '.') ) {
                    ss << expression[i++];
                }
                i--;
                ss >> operand;
                operands.push( operand );
                negative = false;
            }
            // restructurizing the brackets and evaluating theirs content
            else if ( expression[i] == '(' ) {
                operators.push( force_string( expression[i] ) );
                negative = true;
            } else if ( expression[i] == ')' ) {
                while ( !operators.empty() && operators.top() != "(" ) {
                    b = operands.top();
                    operands.pop();

                    a = operands.top();
                    operands.pop();

                    o = operators.top();
                    operators.pop();

                    operands.push( apply_operation( a, b, o ) );
                }
                if ( !operators.empty() )
                    operators.pop(); // pop the '('
                negative = false;
            }
            // dealing with every other operator
            else if ( is_operator( op1 ) || is_operator( op2 ) ) {
                while ( !operators.empty() && precedence( operators.top() ) >= precedence( op1 ) ) {
                    b = operands.top();
                    operands.pop();

                    a = operands.top();
                    operands.pop();

                    o = operators.top();
                    operators.pop();

                    operands.push( apply_operation( a, b, o ) );
                }

                // pushing operators for futher calculating
                if ( is_operator( op2 ) )
                    operators.push( op2 );
                else
                    operators.push( op1 );
                negative = true;
            } else {
                //throw "unknown operator!";
            }
        }

        // the rest of calculating
        while ( !operators.empty() && operands.size() > 1 ) {
            b = operands.top();
            operands.pop();

            a = operands.top();
            operands.pop();

            o = operators.top();
            operators.pop();

            operands.push( apply_operation( a, b, o ) );
        }

        // return result
        if ( operands.size() )
            return operands.top();
        else
            return 0;
    }
}