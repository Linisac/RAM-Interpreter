class registers
{
      public:
             registers( unsigned int );
             registers( unsigned int, int* [] );
             int read_element( unsigned int );
             void write_element( unsigned int, int );
      private:
              unsigned int size;
              int *pArray;
              void enlarge();
              void remedy( unsigned int );
};
