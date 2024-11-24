#include<vector>
#include<string>
#include<iostream>
enum Tokentype{
print,
open_bracket,
close_bracket,
open_paren,
closed_paren,
open_double,
closed_double,
open_single,
closed_single,
string_lit,
integer_lit,
float_lit,
assignment,
identifier,
if_,
elif_,
else_,
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
endoffile
};

struct Token{
Tokentype type;
std::string val;
};

void debug(const Tokentype& token){
    switch (token) {
        case print:           std::cout << "print"; break;
        case open_bracket:    std::cout << "open_bracket"; break;
        case close_bracket:   std::cout << "close_bracket"; break;
        case open_paren:      std::cout << "open_paren"; break;
        case closed_paren:    std::cout << "closed_paren"; break;
        case open_double:     std::cout << "open_double"; break;
        case closed_double:   std::cout << "closed_double"; break;
        case open_single:     std::cout << "open_single"; break;
        case closed_single:   std::cout << "closed_single"; break;
        case string_lit:      std::cout << "string_lit"; break;
        case integer_lit:     std::cout << "integer_lit"; break;
        case float_lit:       std::cout << "float_lit"; break;
        case assignment:      std::cout << "assignment"; break;
        case identifier:      std::cout << "identifier"; break;
        case if_:             std::cout << "if_"; break;
        case elif_:           std::cout << "elif_"; break;
        case else_:           std::cout << "else_"; break;
        case equals:          std::cout << "equals"; break;
        case notequals:       std::cout << "notequals"; break;
        case not_:            std::cout << "not_"; break;
        case lessequals:      std::cout << "lessequals"; break;
        case less:            std::cout << "less"; break;
        case greaterequals:   std::cout << "greaterequals"; break;
        case greater:         std::cout << "greater"; break;
        case or_:             std::cout << "or_"; break;
        case and_:            std::cout << "and_"; break;
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
        case endoffile:       std::cout << "end of file";break;
        default:              std::cout << "Unknown token"; break;
    }
}
class Tokenizer{
public:
    Tokenizer(const std::string& src): src(src){}
    std::vector<Token> tokenize(){
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
        while(peek()!='@'){
            if(tokens.size() && tokens.back().type==Tokentype::open_double){
                while (peek()!='"' && peek()!='\0') {
                    buffer.push_back(consume());
                }
                tokens.push_back({Tokentype::string_lit,buffer});
                buffer.clear();
            }
            if(std::isalpha(peek())){
                buffer.push_back(consume());
                while (std::isalnum(peek())) {
                    buffer.push_back(consume());
                }
                if(buffer=="print"){
                    tokens.push_back({Tokentype::print,""});
                    buffer.clear();
                }
                else if(buffer=="if"){
                    tokens.push_back({Tokentype::if_,"if"});
                    buffer.clear();
                }
                else if(buffer=="else"){
                    tokens.push_back({Tokentype::else_,"else "});
                    buffer.clear();
                }
                else if(buffer=="elif"){
                    tokens.push_back({Tokentype::elif_,"else if"});
                    buffer.clear();
                }
                else if(buffer=="and"){
                    tokens.push_back({Tokentype::and_,"&&"});
                    buffer.clear();
                }
                else if(buffer=="or"){
                    tokens.push_back({Tokentype::or_,"||"});
                    buffer.clear();
                }
                else if(buffer=="not"){
                    tokens.push_back({Tokentype::not_,"!"});
                    buffer.clear();
                }
                else if(buffer=="LINEEND"){
                    //tokens.push_back({Tokentype::endofline,""});
                    buffer.clear();
                }
                else { 
                    tokens.push_back({Tokentype::identifier,buffer});
                    buffer.clear();
                }
            }
            else if(peek()=='('){
                tokens.push_back({Tokentype::open_paren,"("});
                consume();
            }
            else if(peek()==')'){
                tokens.push_back({Tokentype::closed_paren,")"});
                consume();
            }
            else if(peek()=='"'){
                if(check(Tokentype::open_double,Tokentype::closed_double))tokens.push_back({Tokentype::open_double,"\""});
                else tokens.push_back({Tokentype::closed_double,"\""});
                consume();
                buffer.clear();
            }
            // else if(peek()=='\''){
            //     std::cout << "fucker\n";
            //     if(check(Tokentype::open_single,Tokentype::closed_single))tokens.push_back({Tokentype::open_single,""});
            //     else {
            //         std::cout << "fucking\n";
            //         tokens.push_back({Tokentype::closed_single,""});
            //     }
            //     consume();
            //     buffer.clear();
            // } 
            else if (peek()=='='){
                if(peek(1)=='='){
                tokens.push_back({Tokentype::equals,"=="});
                consume();
                }
                else{
                    tokens.push_back({Tokentype::assignment,"="});
                }
                consume();
                buffer.clear();
            }
            else if(peek()=='!' ){
                if(peek(1)=='='){
                    tokens.push_back({Tokentype::notequals,"!="});
                    consume();
                }
                else{
                    tokens.push_back({Tokentype::not_,"!"});
                }
                consume();
                buffer.clear();
            }
            else if(peek()=='<'){
                if(peek(1)=='='){
                    tokens.push_back({Tokentype::lessequals,"<="});
                    consume();
                }
                else{
                    tokens.push_back({Tokentype::less,"<"});
                }
                consume();
                buffer.clear();
            }
            else if(peek()=='>' ){
                if(peek(1)=='='){
                    tokens.push_back({Tokentype::greaterequals,">="});
                    consume();
                }
                else{
                    tokens.push_back({Tokentype::greater,">"});
                }
                consume();
                buffer.clear();
            }
            else if(peek()=='&'){
                tokens.push_back({Tokentype::bitwise_and,"&"});
                consume();
                buffer.clear();
            }
            else if(peek()=='|'){
                tokens.push_back({Tokentype::bitwise_or,"|"});
                consume();
                buffer.clear();
            }
            else if(peek()=='.'){
                if(tokens.size() && tokens.back().type==Tokentype::integer_lit){
                    buffer=tokens.back().val;
                    buffer.push_back(consume());
                    while(std::isdigit(peek())){
                        buffer.push_back(consume());
                    }
                    tokens.back()={Tokentype::float_lit,buffer};
                    buffer.clear();
                }
                else {
                    tokens.push_back({Tokentype::dot,""});
                    consume();
                }
            }
            else if(peek()==':'){
                tokens.push_back({Tokentype::colon,""});
                consume();
                buffer.clear();
            }
            else if(peek()==','){
                tokens.push_back({Tokentype::comma,""});
                consume();
                buffer.clear();
            }
            else if(peek()=='+'){
                if(peek(1)=='='){
                    tokens.push_back({Tokentype::plusequals,"+="});
                    consume();
                }
                else{
                    tokens.push_back({Tokentype::plus,"+"});
                }
                consume();
                buffer.clear();
            }
            else if(peek()=='-'){
                if(peek(1)=='='){
                    tokens.push_back({Tokentype::minusequals,"-="});
                    consume();
                }
                else{
                    tokens.push_back({Tokentype::plus,"-"});
                }
                consume();
                buffer.clear();
            }
            else if(peek()=='*'){
                if(peek(1)=='='){
                    tokens.push_back({Tokentype::mutliplyequals,"*="});
                    consume();
                }
                else{
                    tokens.push_back({Tokentype::mutliply,"*"});
                }
                consume();
                buffer.clear();
            }
            else if(peek()=='/'){
                if(peek(1)=='='){
                    tokens.push_back({Tokentype::divideequals,"/="});
                    consume();
                }
                else{
                    tokens.push_back({Tokentype::divide,"/"});
                }
                consume();
                buffer.clear();
            }
            else if (std::isdigit(peek())) {
                buffer.push_back(consume());
                while (std::isdigit(peek())) {
                    buffer.push_back(consume());
                }
                tokens.push_back({Tokentype::integer_lit,buffer});
                buffer.clear();
            }
            else if(std::isspace(peek())){
                consume();
            }
            else if(peek()=='\0'){
                consume();
                tokens.push_back({Tokentype::endoffile,""});
                break;
            }
            else {
                // std::cout << buffer << std::endl;
                // for(const Token& token:tokens){
                //     std::cout << token.type << " " << token.val << std::endl;
                // }
                std::cerr << "errorrred\n";
                exit(EXIT_FAILURE);
            }
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