#include"tokenizer.cpp"
#include<unordered_set>
#include<sstream>
#include<algorithm>
struct NodeExpr{
    std::vector<Token> identifiertokens;
    std::vector<Token> literals;
    std::string expr;
};

enum TypeNodeStmt{
    Assign,
    Print
};

struct NodeStmt{
    NodeExpr* var;
    TypeNodeStmt type;
};

class Parser{
public:
    Parser(const std::vector<Token>& tokens): tokens(tokens){}
    void parse()
    {
        open();
        while(peek().type!=Tokentype::endoffile)
        {
            NodeStmt* nodestmt=new NodeStmt();
            nodestmt->var=new NodeExpr();
            if(peek().type==Tokentype::print)
            {
                consume();
                try_consume(Tokentype::open_paren,"expected '('");
                while(peek().type!=Tokentype::endofline){
                    nodestmt->var->expr+=peek().val;
                    if(peek().type==Tokentype::identifier)nodestmt->var->identifiertokens.push_back(peek());
                    else if(peek().type==Tokentype::float_lit || peek().type==Tokentype::string_lit) nodestmt->var->literals.push_back(peek());
                    consume();
                }
                nodestmt->var->expr.pop_back();
                nodestmt->type=TypeNodeStmt::Print;
                generate_print(nodestmt);
                //try_consume(Tokentype::closed_paren," expected ')");
                consume();//EOL
            } 
            else if(peek().type==Tokentype::identifier)
            {
                nodestmt->var->expr+=consume().val;
                bool assign=false;
                if(peek().type==Tokentype::assignment){
                    assign=true;
                }
                while(peek().type!=Tokentype::endofline){
                    nodestmt->var->expr+=peek().val;
                    if(peek().type==Tokentype::identifier)nodestmt->var->identifiertokens.push_back(consume());
                    else nodestmt->var->literals.push_back(consume());
                }
                nodestmt->type=TypeNodeStmt::Assign;
                generate_assign(nodestmt);
                consume();//EOL
            }  
            else{
                consume();
                std::cerr << "Not implemented yet\n";
                break;
            }
        }
        close();
    }   
    std::string generate(){
        return stream.str();
    }
private:
    void generate_print(const NodeStmt* nodestmt){
        //check_for_type_error(nodestmt);
        stream << "    cout << " << nodestmt->var->expr << " << endl;\n";
    }
    void generate_assign(const NodeStmt* nodestmt){
        //check_for_type_error(nodestmt);
        stream << "  auto " << nodestmt->var->expr << ";\n";
    }
    void generate_assign_string(const NodeStmt* nodestmt){
        bool float_lit_check=std::any_of(nodestmt->var->literals.cbegin(),nodestmt->var->literals.cend(),
        [](Token token){ return token.type==Tokentype::float_lit;});
        bool string_lit_check=std::any_of(nodestmt->var->literals.cbegin(),nodestmt->var->literals.cend(),
        [](Token token){ return token.type==Tokentype::string_lit;});
        if(float_lit_check)
        {

        }
    }
    void generate_assign_float(const NodeStmt* nodestmt){
        
    }
    void check_for_error(const NodeStmt* nodestmt){
        check_for_type_error(nodestmt);
        check_for_unitiliazed_errors(nodestmt);
    }
    void check_for_type_error(const NodeStmt* nodestmt){
        bool float_lit_check=std::any_of(nodestmt->var->literals.cbegin(),nodestmt->var->literals.cend(),
        [](Token token){ return token.type==Tokentype::float_lit;});
        bool string_lit_check=std::any_of(nodestmt->var->literals.cbegin(),nodestmt->var->literals.cend(),
        [](Token token){ return token.type==Tokentype::string_lit;});

    }
    void check_for_unitiliazed_errors(const NodeStmt* nodestmt){
        bool check=std::any_of(nodestmt->var->identifiertokens.cbegin(),nodestmt->var->identifiertokens.cend(),
        [this](Token token){return stringmap.count(token.val)==0 && floatmap.count(token.val)==0;});
        if(check)
        {
            std::cerr << "unitialized variable\n";
            exit(EXIT_FAILURE);
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
        stream << "    return 0;\n";
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