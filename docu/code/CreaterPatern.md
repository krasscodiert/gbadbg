Example of the Builder in C# for the Instructions 

Builder Interface

    public interface IInstructionBuilder
    {
        public string Opcode { get; set; }

        Instruction GetResult();
    }

Concrete Builder for the Differen Instructions with the same Mask 

    public class JumpBuilder : IInstructionBuilder
    {
        public string Opcode { get; set; }

        public Instruction GetResult()
        {
            return new JumpInstruction(address, ...);        
        }
    }

Concrete Builder for the Differen Instructions with the same Mask 

    public class PushPopBuilder : IInstructionBuilder
    {
        public string Opcode { get; set; }

        public Instruction GetResult()
        {
            return new PushInstruction(...);        
        }
    }

Gives builder all information to create the instruction

    public class InstructionBuildDirector
    {
        private IInstructionBuilder _builder;
        
        public InstructionBuildDirector(IInstructionBuilder builder, string opcode) 
        {
            _builder = builder;
        }

        public void Construct()
        {
            _builder.opcode = opcode;
        }
    }

Less code in parser. Parser no longer has to create all instuctions  

    public class Parser
    {
        public void Parse()
        {
            while(!endOfRom){
                var opcode = getInstruction();
                IInstructionBuilder builder;
                
                switch (InstructionTypes)
                {
                    case JUMP:
                        builder = new JumpBuilder();
                        break;

                    case PUSH:
                        builder = new PushBuilder();
                        break;
                    .
                    .
                    .
                }

                var director = new InstructionBuildDirector(builder, opcode);
                director.Construct();
                Instruction myInstruction = builder.GetResult();
            }
        }
    }