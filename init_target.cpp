#include <systemc>
#include <tlm>
#include <tlm_utils/simple_initiator_socket.h>
#include <tlm_utils/simple_target_socket.h>

class Initiator : public sc_core::sc_module {
  public:
    SC_HAS_PROCESS(Initiator);

    Initiator(sc_core::sc_module_name name):sc_core::sc_module(name) {
      SC_THREAD(hello_ic);
      payload = new tlm::tlm_generic_payload();
      assert(payload != nullptr);
    }

    ~Initiator() {
        delete payload;
    }

  public:
    tlm_utils::simple_initiator_socket<Initiator> init_socket;

  private:
    void hello_ic(){
      const char *data{"message from initiator."};
      payload->set_data_ptr((unsigned char *) data);
      sc_core::sc_time delay = sc_core::SC_ZERO_TIME;

      init_socket->b_transport(*payload, delay);
     }
   
  private:
    tlm::tlm_generic_payload* payload; 
};

class Target:public sc_core::sc_module{
  public:
    SC_HAS_PROCESS(Target);

    Target(sc_core::sc_module_name name):sc_core::sc_module(name) {
      targ_socket.register_b_transport(this, &Target::hello_ic);
    }

  public:
    tlm_utils::simple_target_socket<Target> targ_socket;

  private:
    void hello_ic(tlm::tlm_generic_payload &payload, sc_core::sc_time &delay_time){
      const char *data = reinterpret_cast<const char *>(payload.get_data_ptr());
      std::cout << "target recieve: ";
      std::cout << data << std::endl;
     }
 };


int sc_main(int argc, char* argv[]){
  Initiator init("Initiator");
  Target targ("Target");

  init.init_socket(targ.targ_socket);

  sc_core::sc_start(10, sc_core::SC_NS);

  return 0;
 }