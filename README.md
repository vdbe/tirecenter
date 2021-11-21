# tirecenter

### Running
#### Native

``` sh
make release run
```

#### Docker

1. Build docker image
``` sh
docker build -t tirecenter .
```

2. Create & run container
``` sh
docker run -it --name tirecenter tirecenter
```

3. Run existing container
``` sh
docker start -i tirecenter
```
