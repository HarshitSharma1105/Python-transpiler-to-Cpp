#include<vector>
#include<string>
#include<iostream>
enum Tokentype{
function,
open_bracket,
close_bracket,
open_paren,
closed_paren,
open_double,
closed_double,
open_square,
closed_square,
string_lit,
integer_lit,
float_lit,
assignment,
identifier,
True,
False,
if_,
elif_,
else_,
for_,
in_,
range,
equals,
notequals,
not_,
lessequals,
less,
greaterequals,
greater,
or_,
and_,
bitwise_or,
bitwise_and,
dot,
colon,
comma,
plusequals,
minusequals,
divideequals,
mutliplyequals,
plus,
minus,
mutliply,
divide,
endofline,
indentation,
endoffile
};

struct Token{
Tokentype type;
std::string val;
};

void debug(const Tokentype& token){
    switch (token) {
        case function:           std::cout << "function"; break;
        case open_bracket:    std::cout << "open_bracket"; break;
        case close_bracket:   std::cout << "close_bracket"; break;
        case open_paren:      std::cout << "open_paren"; break;
        case closed_paren:    std::cout << "closed_paren"; break;
        case open_double:     std::cout << "open_double"; break;
        case closed_double:   std::cout << "closed_double"; break;
        case string_lit:      std::cout << "string_lit"; break;
        case integer_lit:     std::cout << "integer_lit"; break;
        case float_lit:       std::cout << "float_lit"; break;
        case assignment:      std::cout << "assignment"; break;
        case identifier:      std::cout << "identifier"; break;
        case True:            std::cout << "true";break;
        case False:           std::cout << "false";break;
        case if_:             std::cout << "if"; break;
        case elif_:           std::cout << "elif"; break;
        case else_:           std::cout << "else"; break;
        case equals:          std::cout << "equals"; break;
        case notequals:       std::cout << "notequals"; break;
        case not_:            std::cout << "not"; break;
        case lessequals:      std::cout << "lessequals"; break;
        case less:            std::cout << "less"; break;
        case greaterequals:   std::cout << "greaterequals"; break;
        case greater:         std::cout << "greater"; break;
        case or_:             std::cout << "or"; break;
        case for_:            std::cout << "for"; break;
        case in_:             std::cout << "in"; break;
        case range:           std::cout << "range"; break;
        case and_:            std::cout << "and"; break;
        case bitwise_or:      std::cout << "bitwise_or"; break;
        case bitwise_and:     std::cout << "bitwise_and"; break;
        case dot:             std::cout << "dot"; break;
        case colon:           std::cout << "colon"; break;
        case comma:           std::cout << "comma"; break;
        case plusequals:      std::cout << "plusequals"; break;
        case minusequals:     std::cout << "minusequals"; break;
        case divideequals:    std::cout << "divideequals";break;
        case mutliplyequals:  std::cout << "mutliplyequals";break;
        case plus:            std::cout << "plus"; break;
        case minus:           std::cout << "minus"; break;
        case divide:          std::cout << "divide"; break;
        case mutliply:        std::cout << "star"; break;
        case endofline:       std::cout << "end of line";break;
        case indentation:     std::cout << "indentation";break;        
        case endoffile:       std::cout << "end of file";break;
        default:              std::cout << "Unknown token"; break;
    }
}
void debug(const std::vector<Token>& tokens){
        std::cout << "-------\n";
        for(const Token& token:tokens){
            debug(token.type);
            if(token.type==Tokentype::indentation)std::cout<< " " << token.val.size();
            std::cout<< " " << token.val << "\n";
        }
        std::cout << "-------\n";
}

class Tokenizer{
public:
    Tokenizer(const std::string& src): src(src){}
    std::vector<Token> tokenize()
    {
        std::vector<Token> tokens;
        std::string buffer;
        auto check=[&](Tokentype type1,Tokentype type2){
            int val=0;
            for(const Token& token:tokens){
                if(token.type==type1)val++;
                else if(token.type==type2)val--;
            }
            return val==0;
        };
        while(true){
            if(tokens.size() && tokens.back().type==Tokentype::open_double)
            {
                while (peek()!='"'){
                    buffer.push_back(consume());
                }
                tokens.push_back({Tokentype::string_lit,buffer});
                buffer.clear();
            }
            if(std::isalpha(peek()))
            {
                buffer.push_back(consume());
                while (std::isalnum(peek()))
                {
                    buffer.push_back(consume());
                }
                if(buffer=="True")
                {
                    tokens.push_back({Tokentype::True,"1"});
                    buffer.clear();
                }
                else if(buffer=="False")
                {
                    tokens.push_back({Tokentype::False,"0"});
                    buffer.clear();
                }
                else if(buffer=="if")
                {
                    tokens.push_back({Tokentype::if_,"if"});
                    buffer.clear();
                }
                else if(buffer=="else")
                {
                    tokens.push_back({Tokentype::else_,"else "});
                    buffer.clear();
                }
                else if(buffer=="elif")
                {
                    tokens.push_back({Tokentype::elif_,"else if"});
                    buffer.clear();
                }
                else if(buffer=="and")
                {
                    tokens.push_back({Tokentype::and_,"&&"});
                    buffer.clear();
                }
                else if(buffer=="or")
                {
                    tokens.push_back({Tokentype::or_,"||"});
                    buffer.clear();
                }
                else if(buffer=="not")
                {
                    tokens.push_back({Tokentype::not_,"!"});
                    buffer.clear();
                }
                else if(buffer=="for")
                {
                    tokens.push_back({Tokentype::for_,"for"});
                    buffer.clear();
                }
                else if(buffer=="in")
                {
                    tokens.push_back({Tokentype::in_,"in"});
                    buffer.clear();
                }
                else if(buffer=="range")
                {

                    tokens.push_back({Tokentype::range,"range"});
                    buffer.clear();
                }
                else 
                { 
                    tokens.push_back({Tokentype::identifier,buffer});
                    buffer.clear();
                }
            }
            else if(peek()=='(')
            {
                if(tokens.size() && tokens.back().type==Tokentype::identifier)
                {
                    tokens.back().type=Tokentype::function;
                }
                tokens.push_back({Tokentype::open_paren,"("});
                consume();
            }
            else if(peek()==')')
            {
                tokens.push_back({Tokentype::closed_paren,")"});
                consume();
            }
            else if (peek()=='[')
            {
                tokens.push_back({Tokentype::open_square,"["});
                consume();
            }
            else if (peek()==']')
            {
                tokens.push_back({Tokentype::open_square,"]"});
                consume();
            }
            else if(peek()=='"')
            {
                if(check(Tokentype::open_double,Tokentype::closed_double))tokens.push_back({Tokentype::open_double,"\""});
                else tokens.push_back({Tokentype::closed_double,"\""});
                consume();
                
            }
           
            else if (peek()=='=')
            {
                if(peek(1)=='=')
                {
                    tokens.push_back({Tokentype::equals,"=="});
                    consume();
                }
                else{
                    tokens.push_back({Tokentype::assignment,"="});
                }
                consume();
            }
            else if(peek()=='!' )
            {
                if(peek(1)=='=')
                {
                    tokens.push_back({Tokentype::notequals,"!="});
                    consume();
                }
                else
                {
                    tokens.push_back({Tokentype::not_,"!"});
                }
                consume();
            }
            else if(peek()=='<')
            {
                if(peek(1)=='=')
                {
                    tokens.push_back({Tokentype::lessequals,"<="});
                    consume();
                }
                else
                {

                    tokens.push_back({Tokentype::less,"<"});
                }
                consume();
            }
            else if(peek()=='>' )
            {
                if(peek(1)=='=')
                {
                    tokens.push_back({Tokentype::greaterequals,">="});
                    consume();
                }
                else
                {
                    tokens.push_back({Tokentype::greater,">"});
                }
                consume();
            }
            else if(peek()=='&')
            {
                tokens.push_back({Tokentype::bitwise_and,"&"});
                consume();
            }
            else if(peek()=='|')
            {
                tokens.push_back({Tokentype::bitwise_or,"|"});
                consume();
            }
            else if(peek()=='.')
            {
                if(tokens.size() && tokens.back().type==Tokentype::integer_lit)
                {
                    buffer=tokens.back().val;
                    buffer.push_back(consume());
                    while(std::isdigit(peek())){
                        buffer.push_back(consume());
                    }
                    tokens.back()={Tokentype::float_lit,buffer};
                    buffer.clear();
                }
                else 
                {
                    tokens.push_back({Tokentype::dot,"."});
                    consume();
                }
            }
            else if(peek()==':')
            {
                tokens.push_back({Tokentype::colon,":"});
                consume();
            }
            else if(peek()==',')
            {
                tokens.push_back({Tokentype::comma,","});
                consume();
            }
            else if(peek()=='+')
            {
                if(peek(1)=='=')
                {
                    tokens.push_back({Tokentype::plusequals,"+="});
                    consume();
                }
                else
                {
                    tokens.push_back({Tokentype::plus,"+"});
                }
                consume();
            }
            else if(peek()=='-')
            {
                if(peek(1)=='=')
                {
                    tokens.push_back({Tokentype::minusequals,"-="});
                    consume();
                }
                else
                {
                    tokens.push_back({Tokentype::plus,"-"});
                }
                consume();
            }
            else if(peek()=='*')
            {
                if(peek(1)=='=')
                {
                    tokens.push_back({Tokentype::mutliplyequals,"*="});
                    consume();
                }
                else
                {
                    tokens.push_back({Tokentype::mutliply,"*"});
                }
                consume();
            }
            else if(peek()=='/')
            {
                if(peek(1)=='=')
                {
                    tokens.push_back({Tokentype::divideequals,"/="});
                    consume();
                }
                else
                {
                    tokens.push_back({Tokentype::divide,"/"});
                }
                consume();
            }
            else if (std::isdigit(peek())) 
            {
                buffer.push_back(consume());
                while (std::isdigit(peek())) 
                {
                    buffer.push_back(consume());
                }
                tokens.push_back({Tokentype::integer_lit,buffer});
                buffer.clear();
            }
            else if(std::isspace(peek()))
            {
                if(tokens.back().type==Tokentype::endofline){
                    std::string space;
                    while(std::isspace(peek())){
                        space+=" ";
                        consume();
                    }
                    tokens.push_back({Tokentype::indentation,space});
                }
                else consume();
            }
            else if(peek()==';')
            {
                consume();
                tokens.push_back({Tokentype::endofline,"\n"});    
                if(!std::isspace(peek()))tokens.push_back({Tokentype::indentation,""});     
            }
            else if(peek()=='\0')
            {
                consume();
                tokens.push_back({Tokentype::endoffile,""});
                break;
            }
            else
            {
                std::cerr << "errorrred from tokenizer\n";
                exit(EXIT_FAILURE);
            }
        }
        for(Token& token:tokens){
            if(token.type==Tokentype::integer_lit)token.type=Tokentype::float_lit;
        }
        return tokens;
    }
private:
char peek(int offset=0){
    if(index+offset>=src.length()){
        return '@';
    }
    return src[index+offset];
}
char consume(){
    return src[index++];
}
std::string src;
int index=0;
};