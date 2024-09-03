class list_nodes_int
{
      friend class linked_lists_int;
      public:
             list_nodes_int( int* );
      private:
              int* pContent;
              list_nodes_int* next;
};

class linked_lists_int
{
      public:
             linked_lists_int();
             void insert_nodes_int( list_nodes_int* );
             unsigned int list_size_int();
             void transfer_int( int* [] );
             ~linked_lists_int();
      private:
              list_nodes_int* head;
              list_nodes_int* tail;
              unsigned int size;
};

class list_nodes_instr
{
      friend class linked_lists_instr;
      public:
             list_nodes_instr( instr_nodes* );
      private:
              instr_nodes* pContent;
              list_nodes_instr* next;
};

class linked_lists_instr
{
      public:
             linked_lists_instr();
             void insert_nodes_instr( list_nodes_instr* );
             unsigned int list_size_instr();
             void transfer_instr( instr_nodes* [] );
             ~linked_lists_instr();
      private:
              list_nodes_instr* head;
              list_nodes_instr* tail;
              unsigned int size;
};
