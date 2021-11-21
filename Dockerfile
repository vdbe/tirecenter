FROM gcc as build-env
RUN mkdir /app
COPY Makefile /app
COPY include /app/include
COPY src /app/src
WORKDIR /app
RUN LDFLAGS=-static make release

FROM scratch
COPY --from=build-env /app/build/tirecenter /tirecenter
CMD ["./tirecenter"]
