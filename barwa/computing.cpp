#include "script.h"

namespace barwa {
	const inline bool script::is_operator( const char c ) {
		return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^');
	}
	
	const inline int_fast8_t script::precedence( const char o ) {
		if ( o == '+' || o == '-' )
			return 1;
		if ( o == '*' || o == '/' )
			return 2;
		if ( o == '^' )
			return 3;
		return 0;
	}

	const inline long double script::apply_operation( const long double a, const long double b, const char o ) {
		switch ( o ) {
			case '+':
				return a + b;
			case '-':
				return a - b;
			case '*':
				return a * b;
			case '/':
				if ( b == 0 ) //throw "error!";
				    return NAN;
                return a / b;
			case '^':
				return pow( a, b );
			default:
				return NAN;
				//throw "error!";
		}
	}

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

    long double script::evaluate( const std::string& expression ) {
        std::stack<char> operators;
        std::stack<long double> operands;
        long double operand, a, b;
        char o;

        // handler of leading negative numbers
        bool wasOperator( true );
        for ( size_t i = 0; i < expression.length(); ++i ) {
            if ( expression[i] == ' ' )
                continue;

            if ( isdigit( expression[i] ) || (expression[i] == '-' && wasOperator && i + 1 < expression.length() && isdigit(expression[i + 1])) ) {
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
                wasOperator = false;
            } else if ( expression[i] == '(' ) {
                operators.push( expression[i] );
                wasOperator = true;
            } else if ( expression[i] == ')' ) {
                while ( !operators.empty() && operators.top() != '(' ) {
                    b = operands.top();
                    operands.pop();

                    a = operands.top();
                    operands.pop();

                    o = operators.top();
                    operators.pop();

                    operands.push( apply_operation( a, b, o ) );
                }
                operators.pop(); // pop the '('
                wasOperator = false;
            } else if ( is_operator( expression[i] ) ) {
                while ( !operators.empty() && precedence( operators.top() ) >= precedence( expression[i] ) ) {
                    b = operands.top();
                    operands.pop();

                    a = operands.top();
                    operands.pop();

                    o = operators.top();
                    operators.pop();

                    operands.push( apply_operation( a, b, o ) );
                }
                operators.push( expression[i] );
                wasOperator = true;
            } else {
                //std::cout << "chuj";
                //throw "unknown operator!";
            }
        }

        while ( !operators.empty() && operands.size() > 1 ) {
            b = operands.top();
            operands.pop();

            a = operands.top();
            operands.pop();

            o = operators.top();
            operators.pop();

            operands.push( apply_operation( a, b, o ) );
        }
        if ( operands.size() )
            return operands.top();
        else
            return 0;
    }
}