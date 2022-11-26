### To install papi in cares2 server

1. login to cares2.
```s
ssh s200010004@cares2.iitdh.ac.in
```

2. clone papi repo.
```s
git clone https://github.com/varendra007/papi.git
```

3. Each time you restart your terminal run this 3 commands.
```s
export PAPI_DIR=/home/s200010004/papi/src/install
export PATH=${PAPI_DIR}/bin:$PATH
export LD_LIBRARY_PATH=${PAPI_DIR}/lib:$LD_LIBRARY_PATH
```

4. Building process.
```s
make DEBUG=1  
```

5. dont't forget to add `./bin/`
```s
./bin/matmul1 64
```

### Git commands

- Adding files to staged area.

 >git add vectorprod_v1.cpp    

- Commiting changes to repo.

> git commit -m "initial commit3"              


- To give the tag.

> git tag -a \<tagname> -m “\<description>”   

- To push tags

> git push --tags

- Pushing all code changes to github.

> git push

- To push specific tag. e.g. git push origin demoTag2    

> git push <remote_name> <tag_name>

- Lists all tags

> git tag

- Deletes local tag

> git tag -delete [or -d] <tag_name> 

- Deletes the remote tag

> git push --delete origin <tag_name> 


![Open in Codespaces](https://classroom.github.com/assets/open-in-codespaces-abfff4d4e15f9e1bd8274d9a39a0befe03a0632bb0f153d0ec72ff541cedbe34.svg)
