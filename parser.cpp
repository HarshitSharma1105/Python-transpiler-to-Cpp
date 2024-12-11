#include"tokenizer.cpp"
#include<unordered_set>
#include<sstream>
#include<algorithm>
struct NodeExpr{
    std::vector<Token> identifiertokens;
    std::vector<Token> literals;
    std::string expr;
    std::string identifier;
};


class Parser{
public:
    Parser(const std::vector<Token>& tokens): tokens(tokens){}
    std::string parse()
    {
        open();
        while(peek().type!=Tokentype::endoffile)
        {
            NodeExpr* Nodeexpr=new NodeExpr();
            if(peek().type==Tokentype::print)
            {
                consume();
                try_consume(Tokentype::open_paren,"expected '('");
                while(peek().type!=Tokentype::endofline){
                    Nodeexpr->expr+=peek().val;
                    if(peek().type==Tokentype::identifier)Nodeexpr->identifiertokens.push_back(peek());
                    else if(peek().type==Tokentype::float_lit || peek().type==Tokentype::string_lit) Nodeexpr->literals.push_back(peek());
                    consume();
                }
                Nodeexpr->expr.pop_back();
                generate_print(Nodeexpr);
                //try_consume(Tokentype::closed_paren," expected ')");
                consume();//EOL
            } 
            else if(peek().type==Tokentype::identifier)
            {
                Nodeexpr->expr+=consume().val;
                Nodeexpr->identifier=Nodeexpr->expr;
                while(peek().type!=Tokentype::endofline){
                    Nodeexpr->expr+=peek().val;
                    if(peek().type==Tokentype::identifier)Nodeexpr->identifiertokens.push_back(peek());
                    else if(peek().type==Tokentype::float_lit || peek().type==Tokentype::string_lit)Nodeexpr->literals.push_back(peek());
                    consume();
                }
                generate_assign(Nodeexpr);
                consume();//EOL
            }  
            else{
                consume();
                std::cerr << "Not implemented yet\n";
                break;
            }
        }
        close();
        return stream.str();
    }   
private:
    void generate_print(const NodeExpr* Nodeexpr){
        check_for_error(Nodeexpr,true);
        stream << "  cout << " << Nodeexpr->expr << " << endl;\n";
    }
    void generate_assign(const NodeExpr* Nodeexpr){
        check_for_error(Nodeexpr,false);
    }
    void generate_assign_string(const NodeExpr* Nodeexpr,bool isassign){
        if(isassign)
        {
            stringmap.insert(Nodeexpr->identifier);
            stream << "  string " << Nodeexpr->expr << ";\n";
        }
        else 
        {
            stream << "  " << Nodeexpr->expr << ";\n";
        }
    }
    void generate_assign_float(const NodeExpr* Nodeexpr,bool isassign){
        if(isassign)
        {
            floatmap.insert(Nodeexpr->identifier);
            stream << "  float " << Nodeexpr->expr << ";\n";
        }
        else 
        {
            stream << "  " << Nodeexpr->expr << ";\n";
        }
    }
    void check_for_error(const NodeExpr* Nodeexpr,bool isprint){
        check_for_type_error(Nodeexpr,isprint);
        check_for_unitiliazed_errors(Nodeexpr);
    }
    void check_for_type_error(const NodeExpr* Nodeexpr,bool isprint){
        bool float_lit_check=std::any_of(Nodeexpr->literals.cbegin(),Nodeexpr->literals.cend(),
        [](Token token){ return token.type==Tokentype::float_lit;});
        bool string_lit_check=std::any_of(Nodeexpr->literals.cbegin(),Nodeexpr->literals.cend(),
        [](Token token){ return token.type==Tokentype::string_lit;});
        bool float_ident_check=std::any_of(Nodeexpr->identifiertokens.cbegin(),Nodeexpr->identifiertokens.cend(),
        [this](Token token){ return floatmap.count(token.val)!=0;});
        bool string_ident_check=std::any_of(Nodeexpr->identifiertokens.cbegin(),Nodeexpr->identifiertokens.cend(),
        [this](Token token){ return stringmap.count(token.val)!=0;});
        if(!isprint)
        {
            if(float_lit_check && string_lit_check)
            {
                std::cerr << " type error found\n";
                exit(EXIT_FAILURE);
            }
            else if(float_lit_check)
            {
                bool assign=floatmap.count(Nodeexpr->identifier)==0;
                generate_assign_float(Nodeexpr,assign);
            }
            else if(string_lit_check)
            {
                bool assign=stringmap.count(Nodeexpr->identifier)==0;
                generate_assign_string(Nodeexpr,assign);
            }  
            else 
            {
                if(string_ident_check && float_ident_check)
                {
                   std::cerr << " type error found\n";
                   exit(EXIT_FAILURE);
                }
                else if(float_ident_check)
                {
                    bool assign=floatmap.count(Nodeexpr->identifier)==0;
                    generate_assign_float(Nodeexpr,assign);
                }
                else if (string_ident_check)
                {
                    bool assign=stringmap.count(Nodeexpr->identifier)==0;
                    generate_assign_string(Nodeexpr,assign);
                }
            }
        }
    }
    void check_for_unitiliazed_errors(const NodeExpr* Nodeexpr){
        bool check=std::any_of(Nodeexpr->identifiertokens.cbegin(),Nodeexpr->identifiertokens.cend(),
        [this](const Token& token){return stringmap.count(token.val)==0 && floatmap.count(token.val)==0;});
        if(check)
        {
            std::cerr << "unitialized variable\n" << Nodeexpr->expr;
            //exit(EXIT_FAILURE);
        }
    }
    void open()
    {
        stream << "#include<iostream>\n";
        stream << "using namespace std;\n";
        stream << "int main(){\n";
    }
    void close()
    {
        stream << "  return 0;\n";
        stream << "}";
    }
    Token peek(int offset=0){
        if(index+offset>=tokens.size()){
            return {Tokentype::endoffile,""};
        }
        return tokens[index+offset];
    }
    Token consume(){
        return tokens[index++];
    }
    Token try_consume(const Tokentype& type, const std::string& err_msg)
    {
        if (peek().type == type) {
            return consume();
        }
        std::cerr << err_msg << std::endl;
        exit(EXIT_FAILURE);
    }

    Token try_consume(const Tokentype& type)
    {
        if (peek().type == type) {
            return consume();
        }
        return {Tokentype::endoffile,""};
    }
private:
    std::vector<Token> tokens;
    int index=0;
    std::unordered_set<std::string> floatmap;
    std::unordered_set<std::string> stringmap;
    std::stringstream stream;
};