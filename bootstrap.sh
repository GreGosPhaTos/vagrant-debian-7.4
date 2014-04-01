#!/usr/bin/env bash
# root user
export DEBIAN_FRONTEND=noninteractive

# configuration
PHP_VERSION=5.5.10
NGINX_VERSION=1.5.12
MYSQL_ROOT_PASSWORD=root

# update aptitude
echo "update aptitude ..."
apt-get update
apt-get -y dist-upgrade
echo "aptitude updated"

# install_vim
echo "install vim ..."
apt-get install -y vim
echo "installation successful !"

# git
# installation
echo "install git ..."
apt-get install -y git-core
echo "installation successful !"

# dependencies
echo "install dependencies ..."
apt-get install -y make bison flex gcc patch autoconf locate libxml2-dev libbz2-dev libpcre3-dev libssl-dev zlib1g-dev libmcrypt-dev libmhash-dev libmhash2 libcurl4-openssl-dev libpng3-dev libjpeg-dev libxslt-dev libmysqlclient15-dev libfreetype6 libfreetype6-dev
echo "dependencies installation successful !"

# php
PHP_DOWNLOAD_URL=http://ca1.php.net/distributions/php-$PHP_VERSION.tar.gz
echo "install PHP ..."
echo "fetching PHP source ..."
cd /usr/local/src/
wget $PHP_DOWNLOAD_URL
tar -xvzf php-$PHP_VERSION.tar.gz
cd php-$PHP_VERSION
echo "configure & install PHP ..."
./configure --enable-fpm --with-mcrypt --with-zlib --enable-mbstring --enable-pdo --with-curl --disable-debug --with-pic --with-openssl --disable-rpath --enable-inline-optimization --with-bz2 --enable-xml --with-zlib --enable-sockets --enable-sysvsem --enable-sysvshm --enable-pcntl --enable-mbregex --with-mhash --with-xsl --enable-zip --with-pcre-regex --with-gd --without-pdo-sqlite --with-pdo-mysql --with-jpeg-dir=/usr/lib --with-png-dir=/usr/lib --with-freetype-dir=/usr/lib --with-mysql --with-mysqli
make && make install
# extensions
echo "php extensions"
#memcached
echo "intalling memcached ..."
apt-get install memcached
pecl uninstall memcache
pecl install memcache
#xdebug
pecl uninstall xdebug
pecl install xdebug
# configurations files 
echo "copying php conf files ..."
strip /usr/local/bin/php-cgi
cp sapi/fpm/init.d.php-fpm /etc/init.d/php-fpm
chmod +x /etc/init.d/php-fpm
cp /vagrant/config/php/php.ini /usr/local/lib/php.ini
rm -R /etc/php/
mkdir /etc/php/
ln -s /usr/local/lib/php.ini /etc/php/php.ini
cp /vagrant/config/php-fpm/php-fpm.conf /usr/local/etc/php-fpm.conf
echo "conf files copied"

# nginx
NGINX_DOWNLOAD_URL=http://nginx.org/download/nginx-$NGINX_VERSION.tar.gz
echo "install NGINX ..."
cd /usr/local/src/
echo "downloadind sources ..."
wget $NGINX_DOWNLOAD_URL
echo "extract sources ..."
tar -xvzf nginx-$NGINX_VERSION.tar.gz
cd nginx-$NGINX_VERSION
echo "configure NGINX ..."
./configure --sbin-path=/usr/local/sbin --with-http_ssl_module --without-mail_pop3_module --without-mail_imap_module --without-mail_smtp_module --with-http_stub_status_module
echo "installation ..."
make & make install
cp /vagrant/config/nginx/nginx /etc/init.d/nginx
cp /vagrant/config/nginx/nginx.conf /usr/local/nginx/conf/nginx.conf
if [ ! -d /usr/local/nginx/vhosts ]; then
	mkdir /usr/local/nginx/vhosts/
fi
cp /vagrant/config/nginx/vhosts/php-dev.example.com.conf /usr/local/nginx/vhosts/php-dev.example.com.conf
echo "installation done !"

# mysql
echo "install mysql ..."
apt-get -q -y install mysql-server
mysqladmin -u root password $MYSQL_ROOT_PASSWORD
apt-get install mysql-client
echo "installation done !"

# mongodb
echo "install mongodb ..."
apt-get -y install mongodb
echo "installation done !"

# phpunit
echo "installing phpunit ..."
wget https://phar.phpunit.de/phpunit.phar
chmod +x phpunit.phar
mv phpunit.phar /usr/local/bin/phpunit
echo "installation done !"

# composer
# need PHP cli
echo "installing composer ..."
if [ ! -d /tmp/exec/ ]; then
	mkdir /tmp/exec/
fi
chmod 0777 /tmp/exec/
cd /tmp/exec/
curl -sS https://getcomposer.org/installer | /usr/local/bin/php
mv composer.phar /usr/local/bin/composer
echo "installation done !"
