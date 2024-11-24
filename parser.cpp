#include"tokenizer.cpp"
#include<unordered_set>
//
//
//
//
// struct NodeTermIntegerLit {
//     Token integer_lit;
// };
// struct NodeTermStringLit{
//     Token string_lit;
// };
// struct NodeTermFloatLit{
//     Token float_lit;
// };


// struct NodeTermIdentifier {
//     Token ident;
// };

// struct NodeNullTerm{
//     Token token;
// };

// struct NodeExpr;

// struct NodeTermParen{
//     NodeExpr* expr;
// };


// struct NodeBinExprAdd {
//     NodeExpr* lhs;
//     NodeExpr* rhs;
// };

// struct NodeBinExprMulti {
//     NodeExpr* lhs;
//     NodeExpr* rhs;
// };

// struct NodeBinExprSub {
//     NodeExpr* lhs;
//     NodeExpr* rhs;
// };

// struct NodeBinExprDiv {
//     NodeExpr* lhs;
//     NodeExpr* rhs;
// };

// union UnionNodeBinExpr{
// NodeBinExprAdd* add;
// NodeBinExprSub* sub;
// NodeBinExprMulti* multi;
// NodeBinExprDiv* divide;
// NodeNullTerm* Null;
// };

// enum TypeNodeBinExpr{
//     Add,
//     Sub,
//     Multi,
//     Division,
//     NullBinExpr,
// };

// struct NodeBinExpr{
//     UnionNodeBinExpr var;
//     TypeNodeBinExpr type;
// };

// struct NodeTermPrint{
//     NodeExpr* var;
// };

// union UnionNodeTerm{
//     NodeTermIntegerLit* intlit;
//     NodeTermFloatLit* floatlit;
//     NodeTermStringLit* stringlit;
//     NodeTermIdentifier* ident;
//     NodeTermParen* paren;
//     NodeTermPrint* print;
//     NodeNullTerm* NodeTermNull;
// };

// enum TypeNodeTerm{
//     IntegerLit,
//     FloatLit,
//     StringLit,
//     Identifer,
//     Paren,
//     Print,
//     NullNodeTerm
// };

// struct NodeTerm{
//     UnionNodeTerm var;
//     TypeNodeTerm type;
// };

// union UnionNodeExpr{
//     NodeTerm* term;
//     NodeBinExpr* Binexpr;
//     NodeNullTerm* null;
// };
// enum TypeNodeExpr{
//     Term,
//     BinExpr,
//     NullNodeExpr,
// };
// struct NodeExpr{
//     UnionNodeExpr var;
//     TypeNodeExpr type;
// };

// struct NodeStmtLetInt {
//     Token integer_ident;
//     NodeExpr* expr;
// };
// struct NodeStmtLetString{
//     Token string_ident;
//     NodeExpr* expr;
// };
// struct NodeStmtLetFloat{
//     Token float_ident;
//     NodeExpr* expr;
// };
// struct NodeStmt;

// // struct NodeScope {
// //     std::vector<NodeStmt*> stmts;
// // };

// // struct NodeIfPred;

// // struct NodeIfPredElif {
// //     NodeExpr* expr;
// //     NodeScope* scope;
// //     NodeIfPred* pred;
// // };

// // struct NodeIfPredElse {
// //     NodeScope* scope;
// // };

// // union UnionNodeIfPred{
// //     NodeIfPredElif* elif;
// //     NodeIfPredElse* else_;
// // };

// // enum TypeNodeIfPred{
// //     Elif,
// //     Else,
// // };

// // struct NodeIfPred {
// //     UnionNodeIfPred* Ifpred;
// //     TypeNodeIfPred type;
// // };


// // struct NodeStmtIf {
// //     NodeExpr* expr{};
// //     NodeScope* scope{};
// //     NodeIfPred* pred;
// // };



// union UnionNodeStmt{
//     NodeStmtLetInt* Int;
//     NodeStmtLetString* Str;
//     NodeStmtLetFloat* Float;
//     //NodeScope* scope;
//     //NodeStmtIf* If_;
//     NodeNullTerm* null;
// };

// enum TypeNodeStmt{
//     Int,
//     Str,
//     Float,
//     //scope,
//     //If,
//     NullNodeStmt,
// };

// struct NodeStmt {
//     UnionNodeStmt var;
//     TypeNodeStmt type;
// };

// struct NodeProg {
//     std::vector<NodeStmt*> stmts;
// };


// class Parser{
// public:
//     Parser(const std::vector<Token>& tokens): tokens(tokens){}
//     NodeTerm* parse_term(){
//         Token integer_lit=try_consume(Tokentype::integer_lit),ident=try_consume(Tokentype::identifier);
//         if(integer_lit.type!=Tokentype::endoffile){
//             NodeTerm* int_lit =new NodeTerm();
//             int_lit->var.intlit->integer_lit=integer_lit;
//             int_lit->type=TypeNodeTerm::IntegerLit;
//             return int_lit;
//         }
//         if(ident.type!=Tokentype::endoffile){
//             NodeTerm* ident_lit=new NodeTerm();
//             ident_lit->var.ident->ident=ident;
//             ident_lit->type=TypeNodeTerm::Identifer;
//             return ident_lit;
//         }
//         NodeTerm* null=new NodeTerm();
//         null->type=TypeNodeTerm::NullNodeTerm;
//         return null;
//     }
//     NodeExpr* parse_expr(){
        
//     }
    
//     NodeStmt* parse_stmt(){
//         if(peek().type==Tokentype::print && peek(1).type==Tokentype::open_paren){
//             consume();
//             consume();
//             if(peek().type==Tokentype::open_double){
//                 consume();
//                 if(peek().type==Tokentype::string_lit){
//                     NodeStmt* string_lit=new NodeStmt();
//                     string_lit->var=*new UnionNodeStmt();
//                     string_lit->var.Str=new NodeStmtLetString();
//                     string_lit->var.Str->string_ident=consume();
//                     string_lit->type=TypeNodeStmt::Str;
//                     try_consume(Tokentype::closed_double,"expected '\" ' ");
//                     try_consume(Tokentype::closed_paren,"expected )");
//                     return string_lit;
//                 }
//             }
//             else if(peek().type==Tokentype::integer_lit){
//                 NodeStmt* int_lit=new NodeStmt();
//                 int_lit->var=*new UnionNodeStmt();
//                 int_lit->var.Int=new NodeStmtLetInt();
//                 int_lit->var.Int->integer_ident=consume();
//                 int_lit->type=TypeNodeStmt::Str;
//                 try_consume(Tokentype::closed_paren,"expected )");
//                 return int_lit;
//             }
//             else if(peek().type==Tokentype::float_lit){
//                 NodeStmt* float_lit=new NodeStmt();
//                 float_lit->var=*new UnionNodeStmt();
//                 float_lit->var.Float=new NodeStmtLetFloat();
//                 float_lit->var.Float->float_ident=consume();
//                 float_lit->type=TypeNodeStmt::Str;
//                 try_consume(Tokentype::closed_paren,"expected )");
//                 return float_lit;
//             }
//             else if(peek().type==Tokentype::identifier){
//                 consume();
//                 try_consume(Tokentype::closed_paren,"expected )");
//                 // return ident;
//             }
//             else{
//                 std::cerr << "unreachable\n";
//                 exit(EXIT_FAILURE);
//             }
//         }
//         NodeStmt* null=new NodeStmt();
//         null->type=TypeNodeStmt::NullNodeStmt;
//         return null;
//     }
//     NodeProg parse_prog(){
//         NodeProg prog;
//         while (peek().type!=Tokentype::endoffile) {
//             NodeStmt* stmt=parse_stmt();
//             if (stmt->type!=TypeNodeStmt::NullNodeStmt) {
//                 prog.stmts.push_back(stmt);
//             }
//             else {
//                 std::cerr << "Invalid statement" << std::endl;
//                 exit(EXIT_FAILURE);
//             }
//         }
//         return prog;
//     }
// private:
//     Token peek(int offset=0){
//         if(index+offset>=tokens.size()){
//             return {Tokentype::endoffile,""};
//         }
//         return tokens[index+offset];
//     }
//     Token consume(){
//         return tokens[index++];
//     }
//      Token try_consume(const Tokentype& type, const std::string& err_msg)
//     {
//         if (peek().type == type) {
//             return consume();
//         }
//         std::cerr << err_msg << std::endl;
//         exit(EXIT_FAILURE);
//     }

//     Token try_consume(const Tokentype& type)
//     {
//         if (peek().type == type) {
//             return consume();
//         }
//         return {Tokentype::endoffile,""};
//     }
//     std::vector<Token> tokens;
//     int index=0;
// };

struct NodeInt{
    Token Int;
    Token ident;
};
struct NodeFloat{
    Token Float;
    Token ident;
};
struct NodeString{
    Token String;
    Token ident;
};
struct NodePrint{
    Token Print;
    Token ident;
};
union UnionNodeStmt{
    NodeInt* Int;
    NodeFloat* Float;
    NodeString* String;
    NodePrint* Print;
};

enum TypeNodeStmt{
    Int,
    Float,
    String,
    Print
};

struct NodeStmt{
    UnionNodeStmt* var;
    TypeNodeStmt type;
};

struct NodeProg{
    std::vector<NodeStmt*> NodeStmts;
};

class Parser{
public:
    Parser(const std::vector<Token>& tokens): tokens(tokens){}
    NodeProg parse()
    {
        NodeProg prog;
        while(peek().type!=Tokentype::endoffile)
        {
            if(peek().type==Tokentype::print)
            {
                NodeStmt* nodestmt=new NodeStmt();
                nodestmt->var=new UnionNodeStmt();
                nodestmt->var->Print=new NodePrint();
                consume();
                try_consume(Tokentype::open_paren,"expected '('");
                if(peek().type==Tokentype::open_double)
                {
                    consume();
                    nodestmt->var->Print->Print=consume();
                    try_consume(Tokentype::closed_double,"expected '\"");

                }
                else 
                {
                    nodestmt->var->Print->Print=consume();
                }
                nodestmt->type=TypeNodeStmt::Print;
                prog.NodeStmts.push_back(nodestmt);
                try_consume(Tokentype::closed_paren," expected ')");
            } 
            else if(peek().type==Tokentype::identifier)
            {
                std::string buffer="";
                buffer+=consume().val;
                if(peek().type==Tokentype::assignment)
                {
                    buffer+=consume().val;
                    NodeStmt* nodestmt=new NodeStmt();
                    nodestmt->var=new UnionNodeStmt();
                    if(peek().type==Tokentype::integer_lit){
                        nodestmt->var->Int=new NodeInt();
                        // std::unordered_set<Tokentype> conitn={Tokentype::plus,Tokentype::minus,Tokentype::divide,Tokentype::mutliply,Tokentype::closed_paren,Tokentype::open_paren,Tokentype::identifier};
                        // while(conitn.find(peek().type)!=conitn.end())
                        // {
                        //     buffer+=consume().val;
                        // }
                        buffer+=consume().val;
                        nodestmt->var->Int->Int.val=buffer;
                        buffer.clear();
                        nodestmt->type=TypeNodeStmt::Int;
                    }
                    else if(peek().type==Tokentype::float_lit){
                        nodestmt->var->Float=new NodeFloat();
                        // std::unordered_set<Tokentype> conitn={Tokentype::plus,Tokentype::minus,Tokentype::divide,Tokentype::mutliply,Tokentype::closed_paren,Tokentype::open_paren,Tokentype::identifier};
                        // while(conitn.find(peek().type)!=conitn.end())
                        // {
                        //     buffer+=consume().val;
                        // }
                        buffer+=consume().val;
                        nodestmt->var->Float->Float.val=buffer;
                        buffer.clear();
                        nodestmt->type=TypeNodeStmt::Float;
                    }
                    else if(peek().type==Tokentype::open_double)
                    {
                        nodestmt->var->String=new NodeString();
                        buffer+=consume().val;
                        buffer+=consume().val;
                        buffer+=try_consume(Tokentype::closed_double,"expected \"").val;
                        nodestmt->var->String->String.val=buffer;
                        nodestmt->type=TypeNodeStmt::String;
                        buffer.clear();
                    }
                    else
                    {
                        std::cerr << "Not implemented yeteeee\n";
                        exit(EXIT_FAILURE);
                    }
                    prog.NodeStmts.push_back(nodestmt);
                }
            }  
            else{
                std::cerr << "Not implemented yet\n";
                break;
            }
        }
        return prog;
    }   
private:
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
    std::vector<Token> tokens;
    int index=0;
};