# SPWS v0.2 (beta)
## About 
SPWS is simple web server. Suitable for hosting your portfolio in the internet.  
The web server is being configures in spws.conf file, usually located in "/usr/local/etc/spws/spws.conf".

## Configuration
Configuration file located at "/usr/local/etc/spws/spws.conf"  
Example: 
```config
body {
    server {
        port 80
        target / {
            /var/www
        }
        target /images/ {
            /var/www/data
        }
    }
}
```