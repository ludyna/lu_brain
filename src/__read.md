sd: hoea

$ valgrind ./bin/fam_initialization


to test one:

ceedling test:recs
ceedling test:pyra_layer    



	+ Any type or method that is visible to END users should start with "lu_" prefix. Typedefs of pointers for END users should be prefixed with "Lu" (Lu_Brain, LuNeuron).

	+ Prefixes "lu_", "Lu" should avoided in internal code (exception are types defined in global/lu_types.h). "LU_" is used in internal code as prefix to "header" defines (LU_NEU_H, LU_MEM_ALLOC_H) and constants.


	Hello,

Thank you for contacting DigitalOcean support !

You are using GoDaddy for DNS so you are getting this error when trying to generate NS record. If you want to install a free - LetsEncrypt certificate then you will need update NS record pointing to DigitalOcean. 

In order to update the nameserver to DigitalOcean, please contact your domain registrar and update the following records:

ns1.digitalocean.com. 173.245.58.51
ns2.digitalocean.com. 173.245.59.41
ns3.digitalocean.com. 198.41.222.173

​​​​​​​https://www.digitalocean.com/community/tutorials/how-to-point-to-digitalocean-nameservers-from-common-domain-registrars

We're more than happy to help if you get stuck or have a question, however, please don't hesitate to ask. 

Regards,

Dikshith
Developer Support Engineer II
Don't forget to check out our fantastic community articles!
https://www.digitalocean.com/community