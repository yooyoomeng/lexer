#include <bits/stdc++.h>
using namespace std;
enum TokenType {
    // struct keywords
    Var,
    If,
    Then,
    Else,
    While,
    Do,
    Begin,
    End,

    // operator keywords
    And,
    Or,

    // type keywords
    Integer,
    Longint,
    Bool,
    Real,

    // operators +|-|*|/|:=|<|>|<>|>=|<=|=|:|(|)
    /// +
    Add,
    /// -
    Sub,
    /// *
    Mul,
    /// /
    Div,
    /// :=
    Assign,
    /// <
    Lt,
    /// >
    Gt,
    /// <>
    Ne,
    /// >=
    Ge,
    /// <=
    Le,
    /// =
    Eq,
    /// :
    Colon,
    /// (
    LParen,
    /// )
    RParen,

    // struct symbols
    /// ,
    Comma,
    /// ;
    SemiColon,

    // Literals and Identifiers
    /// Identifier [a-zA-Z][a-zA-Z0-9]*, case insensitive
    Ident,
    /// Integer literal [1-9][0-9]*|0, no leading 0
    IntLiteral,
};
struct Token {
    TokenType type;
    int start;
    string content;
};
#define match_keyword(s, ty) \
    if (lett == s)           \
        return Token { ty, start, lett }

struct Lexer {
    string src;
    int pos;
    optional<Token> next_token() {
        while (pos < src.size() && isspace(src[pos])) {
            pos++;
        }
        if (pos == src.size()) {
            return {};
        }

        int start = pos;
        if (isalpha(src[pos])) {

            string lett = "";
            while (pos < src.size() && isalnum(src[pos])) {
                lett += src[pos];
                pos++;
            }
            transform(lett.begin(), lett.end(), lett.begin(), ::tolower);
            match_keyword("var", Var);
            match_keyword("if", If);
            match_keyword("then", Then);
            match_keyword("else", Else);
            match_keyword("while", While);
            match_keyword("do", Do);
            match_keyword("begin", Begin);
            match_keyword("end", End);
            match_keyword("and", And);
            match_keyword("or", Or);
            match_keyword("integer", Integer);
            match_keyword("longint", Longint);
            match_keyword("bool", Bool);
            match_keyword("real", Real);
            return Token{Ident, start, lett};
        } else if (isdigit(src[pos])) {
            string lett = "";
            while (pos < src.size() && isdigit(src[pos])) {
                lett += src[pos];
                pos++;
            }
            if (pos < src.size() && isalpha(src[pos])) {
                cerr << lett << src[pos] << " invalid integer literal" << endl;
                throw "invalid integer literal";
            }
            return Token{IntLiteral, start, lett};
        } else if (src[pos] == ':' && pos < src.size() + 1 && src[pos + 1] == '=') {
            pos += 2;
            return Token{Assign, start, ":="};
        } else if (src[pos] == '<' && pos < src.size() + 1 && src[pos + 1] == '=') {
            pos += 2;
            return Token{Le, start, "<="};
        } else if (src[pos] == '>' && pos < src.size() + 1 && src[pos + 1] == '=') {
            pos += 2;
            return Token{Ge, start, ">="};
        } else if (src[pos] == '<' && pos < src.size() + 1 && src[pos + 1] == '>') {
            pos += 2;
            return Token{Ne, start, "<>"};
        } else if (src[pos] == ':') {
            pos++;
            return Token{Colon, start, ":"};
        } else if (src[pos] == ',') {
            pos++;
            return Token{Comma, start, ","};
        } else if (src[pos] == ';') {
            pos++;
            return Token{SemiColon, start, ";"};
        } else if (src[pos] == '+') {
            pos++;
            return Token{Add, start, "+"};
        } else if (src[pos] == '-') {
            pos++;
            return Token{Sub, start, "-"};
        } else if (src[pos] == '*') {
            pos++;
            return Token{Mul, start, "*"};
        } else if (src[pos] == '/') {
            pos++;
            return Token{Div, start, "/"};
        } else if (src[pos] == '<') {
            pos++;
            return Token{Lt, start, "<"};
        } else if (src[pos] == '>') {
            pos++;
            return Token{Gt, start, ">"};
        } else if (src[pos] == '=') {
            pos++;
            return Token{Eq, start, "="};
        } else if (src[pos] == '(') {
            pos++;
            return Token{LParen, start, "("};
        } else if (src[pos] == ')') {
            pos++;
            return Token{RParen, start, ")"};
        } else {
            cerr << src[pos] << " Unexpected character" << endl;
            throw "Unexpected character";
        }
        // unimplemented
    }
};
#undef match_keyword
struct PreGrammar {

    vector<Token> tokens;
    int pos;

    void parse_var_block() {
        if (!(pos < tokens.size() && tokens[pos].type == Var)) {
            cerr << tokens[pos].content << " except a Var" << endl;
            throw "missing Var";
        }
        pos++;
        int flag;

        while (pos < tokens.size()) {

            while (pos < tokens.size()) {

                if (tokens[pos].type != Ident) {
                    cerr << tokens[pos].content << " not a valid Ident" << endl;
                    throw "invalid Ident";
                } else {

                    pos++;
                }
                if (pos < tokens.size() && tokens[pos].type == Comma) {
                    pos++;
                    continue;
                } else if (pos < tokens.size() && tokens[pos].type == Colon) {
                    pos++;
                    break;
                } else {
                    cerr << tokens[pos].content << " except a ,or:" << endl;
                    throw "missing , or :";
                }
            }
            if (pos < tokens.size() && (tokens[pos].type == Integer || tokens[pos].type == Bool || tokens[pos].type == Real || tokens[pos].type == Longint)) {
                pos++;
                if (pos < tokens.size() && tokens[pos].type == SemiColon) {
                    pos++;
                } else {
                    cerr << tokens[pos].content << " except a ;" << endl;
                    throw "missing ;";
                }
            } else {

                cerr << tokens[pos].content << " except a valid type" << endl;
                throw "invalid type";
            }

            if (pos < tokens.size() && tokens[pos].type == Begin) {
                break;
            } else if (pos >= tokens.size()) {
                cerr << tokens[pos].content << " except a Begin" << endl;
                throw "missing Begin";
            }
        }
    }
    void parse_program_block() {
        throw "Unimplemented";
        while (1) {
            // auto token = lexer.next_token();
        }
    }
    void parse_code() {

        parse_var_block();
        parse_program_block();
    }
};
vector<Token> lex(string src) {
    auto lexer = Lexer{src, 0};
    vector<Token> tokens;
    while (1) {
        auto token = lexer.next_token();
        if (!token.has_value()) {
            return tokens;
        }
        tokens.push_back(token.value());
    }
}
int main(int argc, char *argv[]) {
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <filename>\n";
        return 1;
    }
    auto filename = string(argv[1]);

    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Could not open the file\n";
        return 1;
    }
    string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

    auto tokens = lex(content);

    auto pre_grammar = PreGrammar{tokens, 0};
    pre_grammar.parse_code();
    // errors
    return 0;
}
