#%%
import os


# %%
pipe_name="MY_PIPE"
fd=os.open(pipe_name,os.O_RDONLY)
while True:
    out=os.read(fd,10)

    print(out)