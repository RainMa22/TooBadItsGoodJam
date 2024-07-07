# quick tool to generate preset... out of time sorry

import random
for j in range(2):
    with open("\\".join(["presets",f"{j}.txt"]),"w") as file:
        file.write(f"{j**2} 0 0\n")
        file.write(f"{(j+1)**2} {j+1} 0\n")
        frames_per_percent = 600
        file.write(f"{(j+2)**2} {(j+1)*2} {frames_per_percent}\n")
        for i in range(2,255,1):
            diff = -random.getrandbits(j+1)
            frames_per_percent += diff
            file.write(f"{i**(2+j)} {+random.getrandbits(j+1)} {diff if frames_per_percent > 1 else 0}")
            file.write("\n")
        file.close()