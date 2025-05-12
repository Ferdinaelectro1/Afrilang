#include "ASTNode.h"

//ASTNode::ASTNode() {}

std::string NumberNode::toCpp() const 
{
    return value;
}

OperationNode::OperationNode(std::unique_ptr<ASTNode> l, std::string op, std::unique_ptr<ASTNode> r) : op(op),left(std::move(l)),right(std::move(l)) {}

std::string OperationNode::toCpp() const
{
    return "("+left->toCpp()+op+right->toCpp()+")";
}

std::string VariableNode::toCpp() const
{
    return name;
}

std::string PrintNode::toCpp() const
{
    return "std::cout <<"+chaine->toCpp()+"<< std::endl;";
}

std::string EqualNode::toCpp() const
{
    return "double "+variable->toCpp()+" = "+value->toCpp()+";";
}