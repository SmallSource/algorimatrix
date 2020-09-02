//
// Created by colors_wind on 2020/8/24.
//

#include "Token.h"
#include <sstream>
using std::to_string;

string Token::toString() const {
    switch(m_type) {
        case OPERATOR:
            return string("Operator{'") + asChar() + "'}";
        case DELIMITER:
            return string("Delimiter{'") + asChar() + "'}";
        case NUMBER:
            return string("Number{") + to_string(asNumber()) + "}";
        case VARIABLE:
            return string("Variable{\"") + asString() + "\"}";
        case FUNCTION_1:
            return string("Function1{") + getRawText() + "}";
        case FUNCTION_2:
            return string("Function2{") + getRawText() + "}";
        case END:
            return "END{}";
        default:
            return "Unknown";
    }
}

Token::Token(TokenType type, void *p, const string &origin): m_type(type), m_value(p), m_origin(origin) {}

Token::~Token() {
    if (m_value != NULL) {
        switch(m_type) {
            case OPERATOR:
            case DELIMITER:
                delete (char*)m_value;
                break;
            case NUMBER:
                delete (double *)m_value;
                break;
            case VARIABLE:
                delete (string*)m_value;
                break;
        }
        m_value = NULL;
    }
}

Token &Token::operator=(const Token &token) {
    this ->m_type = token.m_type;
    this ->m_value = token.copyValue();
    return *this;
}


Token::Token(const Token & token): m_type(token.m_type), m_value(token.copyValue()) {}

string Token::asString() const {
    return *(string*)m_value;
}

char Token::asChar() const {
    return *(char*)m_value;
}

double Token::asNumber() const {
    return *(double*)m_value;
}

Func1 Token::asFunction1() const {
    return (Func1)m_value;
}

Func2 Token::asFunction2() const {
    return (Func2)m_value;
}

Token::Token(TokenType type, double d, const string &origin) : m_type(type), m_value(new double(d)), m_origin(origin){}
Token::Token(TokenType type, char c, const string &origin) : m_type(type), m_value(new char(c)), m_origin(origin){}
Token::Token(TokenType type, string str, const string &origin) : m_type(type), m_value(new string(str)), m_origin(origin){}
Token::Token(TokenType type, const string &origin) : m_type(type), m_value(NULL), m_origin(origin) {}

bool Token::isEquls(char c) const {
    switch (m_type) {
        case OPERATOR:
        case DELIMITER:
            if (asChar() == c) return true;
    }
    return false;
}

TokenType Token::getType() const {
    return m_type;
}

void *Token::copyValue() const {
    switch(m_type) {
        case OPERATOR:
        case DELIMITER:
            return new char(asChar());
        case NUMBER:
            return new double(asNumber());
        case VARIABLE:
            return new string(asString());
        case FUNCTION_1:
            return new Func1(asFunction1());
        case FUNCTION_2:
            return new Func2(asFunction2());
        case END:
        default:
            return NULL;
    }
}

const string &Token::getRawText() const {
    return m_origin;
}

