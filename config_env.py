import textwrap


def increase_env():
    env_path = "/etc/profile"
    env = """
        export JAVA_HOME=/rt-thread/jdk-11.0.1 
        export JRE_HOME=${JAVA_HOME}/jre  
        export CLASSPATH=.:${JAVA_HOME}/lib:${JRE_HOME}/lib  
        export PATH=${JAVA_HOME}/bin:$PATH
        """
    env = textwrap.dedent(env)
    with open(env_path, 'a') as f:
        f.write(env)


if __name__ == "__main__":
    increase_env()
