module Compute where

import Structures

compute :: Environment -> Expression -> (Environment, Expression)
compute environment Null = (environment, Null)
compute environment (Boolean bool) = (environment, Boolean bool)
compute environment (Number number) = (environment, Number number)
compute environment (Chars str) = (environment, Chars str)
compute environment (Pair str1 str2) = (environment, Pair str1 str2)
compute environment (Variable variable) =
  (environment, searchInEnv environment variable)
compute environment procedure@(Lambda _ _) =
  (environment, procedure)
compute environment other = computeDefinition environment other

computeDefinition :: Environment -> Expression -> (Environment, Expression)
computeDefinition environment expr@(Definition _ _) = 
  defSpecialCase environment expr
computeDefinition environment other = computePredicate environment other

computePredicate :: Environment -> Expression -> (Environment, Expression)
computePredicate environment (If predicate thenClause elseClause)
  | result == True = compute newEnvironment thenClause
  | otherwise = compute newEnvironment elseClause
  where (newEnvironment, (Boolean result)) = compute environment predicate
computePredicate environment other = computeCond environment other

computeCond :: Environment -> Expression -> (Environment, Expression)
computeCond environment (Cond []) =
  (environment, (Exception "No case in cond special form matches."))
computeCond environment (Cond ((predicate, expression):xs))
  | result = compute newEnvironment expression
  | otherwise = compute newEnvironment (Cond xs)
  where (newEnvironment, (Boolean result)) = compute environment predicate
computeCond environment other = computeApp environment other

computeApp :: Environment -> Expression -> (Environment, Expression)
computeApp environment (Application operator operands) =
  opCase finalEnvironment op exception arguments firstEnvironment
  where (firstEnvironment, op) = compute environment operator
        (finalEnvironment, arguments) = computeList firstEnvironment operands
        exception = firstException arguments
computeApp environment _ = (environment, Exception exceptStr)

opCase :: Environment -> Expression -> Maybe Expression
  -> [Expression] -> Environment -> (Environment, Expression)
opCase env (Procedure procedure) exception params _ = case exception of
  Just e -> (env, e)
  Nothing -> (env, procedure params)
opCase env (Lambda params body) _ args _ = (env, result)
  where nEnv = extendEnvironment env params args
        (_, result) = compute nEnv body
opCase _ _ _ _ firstEnvironment = (firstEnvironment, Exception nProcedureStr)

-- Special case

defSpecialCase :: Environment -> Expression -> (Environment, Expression)
defSpecialCase env expr@(Definition variable expression) =
  ((addPairToEnv newEnvironment symbol value), value)
  where (newEnvironment, value) = compute env expression
        (Variable symbol) = variable

-- Constants
nProcedureStr :: String
nProcedureStr = "Error: expression is not a procedure."

exceptStr :: String
exceptStr = "Error: Can't compute, not supported"

computeSequence :: Environment -> [Expression] -> (Environment, Expression)
computeSequence environment [] = (environment, Null)
computeSequence environment [e] = compute environment e
computeSequence environment (e:es) = computeSequence env1 es
  where (env1, _) = compute environment e
--      result ↑

computeList :: Environment -> [Expression] -> (Environment, [Expression])
computeList environment [] = (environment, [])
computeList environment (e:es) =
  let (firstEnvironment, resultFirst) = compute environment e
      (finalEnvironment, resultFinal) = computeList firstEnvironment es
  in (finalEnvironment, resultFirst : resultFinal)

firstException :: [Expression] -> Maybe Expression
firstException [] = Nothing
firstException (e:es) = case e of
  (Exception _) -> Just e
  _ -> firstException es