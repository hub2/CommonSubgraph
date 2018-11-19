import time
import os
import subprocess

graph_cli = './GraphCli/GraphCli create random -p 0.7 -v %d -o ./examples/random_%d/%d_%d_%s_barc.csv'
exact = './Calculation/commonSubgraph %s %s ./examples/random_%d/exact.csv 1'
approx = './Calculation/commonSubgraph %s %s ./examples/random_%d/approx.csv'
time_approx = []                   
time_exact = []                    
for i in range(7, 11):             
    for j in range(3):              
        k = j+i                     
        os.makedirs("./examples/random_%d" % (i*10+j), exist_ok=True)
        file_1 = "./examples/random_%d/%d_%d_A_barc.csv" % ((i*10+j), i, k)
        file_2 = "./examples/random_%d/%d_%d_B_barc.csv" % ((i*10+j), i, k)
        cmd_1 = graph_cli % (i, i*10+j, i, k, "A")
        print(cmd_1)
        subprocess.check_output(cmd_1.split())
        cmd_2 = graph_cli % (k, i*10+j, i, k, "B")
        print(cmd_2)
        subprocess.check_output(cmd_2.split())    
        
        cmd_3 = exact % (file_1, file_2, i*10+j)
        cmd_4 = approx % (file_1, file_2, i*10+j)
        
        t1 = time.time()
        subprocess.check_output(cmd_3.split())
        t2 = time.time()
        t_exact = (t2-t1) * 1000.0
        found_graph_size = subprocess.check_output(["wc", "-l", "./examples/random_%d/exact.csv" % (i*10+j)]).split()[0]
        
        time_exact.append((i, k, t_exact, found_graph_size))
        
        t1 = time.time()
        subprocess.check_output(cmd_4.split())
        t2 = time.time() 
        t_approx = (t2-t1) * 1000.0
        found_graph_size = subprocess.check_output(["wc", "-l", "./examples/random_%d/approx.csv" % (i*10+j)]).split()[0]
        time_approx.append((i, k, t_approx, found_graph_size))

