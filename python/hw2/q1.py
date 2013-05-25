# Jarret Shook
# HW2 Question 1

class stack:

   def __init__(self):
      
      self.m_list = list()

   def push(self, _Value):
      
      self.m_list.append(_Value)

   def pop(self):

      if (len(self.m_list) > 0): return self.m_list.pop()

      else: return None

   def size(self):

      return len(self.m_list)

class parentheses:

   def __init__(self, _Index, _Parentheses):

      self.m_parentheses = _Parentheses
      self.m_index = _Index

   def get_index(self):

      return self.m_index

   def get_parentheses(self):

      return self.m_parentheses

def checkParen(_String):

   _Stack = stack()

   _Index = 0

   for _Char in _String:

      if (_Char == '('): _Stack.push(parentheses(_Index, _Char))

      else:

         _ReturnValue = _Stack.pop()

         if (_ReturnValue == None): return _Index;

      _Index += 1


   if (_Stack.size() != 0):
      
      while (_Stack.size() != 1 and _Stack.size() > 0): _Stack.pop()

      return _Stack.pop().get_index()

   else: return -1

if __name__=="__main__":
   
   # Test code

   print checkParen("(()")
   print checkParen(")()")

   print checkParen("()()()(((((())))))")
   print checkParen("()()()()()(())()")

   print checkParen("()()()(((()))))))))))")
   print checkParen("(((((((())))))))(()")
