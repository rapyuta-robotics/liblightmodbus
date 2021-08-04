#include "tester.hpp"

void last_register_tests()
{
	run_test("Reading last coils/registers", [](){
		set_mode("pdu");
		for (int i = 1; i <= 4; i++)
		{
			build_request({1, i, 65535, 1});
			dump_request();
			parse_request();
			assert_slave(1);
			parse_response();
			assert_master(1);
			dump_data();
		}
	});

	run_test("Reading two last coils/registers", [](){
		for (int i = 1; i <= 4; i++)
		{
			set_mode("pdu");
			build_request({1, i, 65534, 2});
			dump_request();
			parse_request();
			assert_slave(1);
			parse_response();
			assert_master(1);
			dump_data();
		}
	});

	run_test("Reading one past the last coil/register", [](){
		set_mode("pdu");
		for (int i = 1; i <= 4; i++)
		{
			build_request({1, i, 65535, 2});
			assert_master(0);

			set_request({i, 255, 255, 0, 2});
			dump_request();
			parse_request();
			dump_slave();
			assert_slave_ex(MODBUS_EXCEP_ILLEGAL_ADDRESS);
		}
	});
}

void max_read_tests()
{
	run_test("Reading 2000 coils/discrete inputs", [](){
		set_mode("pdu");
		for (int i = 1; i <= 2; i++)
		{
			build_request({1, i, 0, 2000});
			assert_master(1);
			parse_request();
			dump_slave();
			assert_slave_ex(MODBUS_EXCEP_NONE);
			parse_response();
			assert_master(1);
		}
	});

	run_test("Reading 2001 coils/discrete inputs", [](){
		set_mode("pdu");
		for (int i = 1; i <= 2; i++)
		{
			build_request({1, i, 0, 2001});
			dump_master();
			assert_master(0);

			set_request({i, 0, 0, 0x07, 0xd1});
			parse_request();
			dump_slave();
			assert_slave_ex(MODBUS_EXCEP_ILLEGAL_VALUE);
			parse_response();
			assert_master(1);
		}
	});

	run_test("Reading 125 input/holding registers", [](){
		set_mode("pdu");
		for (int i = 3; i <= 4; i++)
		{
			build_request({1, i, 0, 125});
			assert_master(1);
			parse_request();
			dump_slave();
			assert_slave_ex(MODBUS_EXCEP_NONE);
			parse_response();
			assert_master(1);
		}
	});

	run_test("Reading 126 input/holding registers", [](){
		set_mode("pdu");
		for (int i = 3; i <= 4; i++)
		{
			build_request({1, i, 0, 126});
			dump_master();
			assert_master(0);

			set_request({i, 0, 0, 0x00, 0x74});
			parse_request();
			dump_slave();
			assert_slave_ex(MODBUS_EXCEP_ILLEGAL_VALUE);
			parse_response();
			assert_master(1);
		}
	});
}

void modbus_pdu_tests()
{
	run_test("Parse empty PDU request frame", [](){
		set_mode("pdu");
		set_request({});
		parse_request();
		assert_slave(0);
	});

	run_test("Parse empty PDU response frame", [](){
		set_mode("pdu");
		set_response({});
		parse_response();
		assert_master(0);
	});
}

void modbus_rtu_tests()
{
	run_test("Parse a raw Modbus RTU request (write register)", [](){
		set_mode("rtu");
		set_request({0x01, 0x06, 0xab, 0xcd, 0x01, 0x23, 0x78, 0x58});
		parse_request();
		assert_slave(1);
		assert_reg(0xabcd, 0x0123);
		dump_response();
		parse_response();
		assert_master(1);
	});

	run_test("Parse a raw Modbus RTU request with invalid CRC (big-endian)", [](){
		set_mode("rtu");
		set_request({0x01, 0x06, 0xab, 0xcd, 0x01, 0x23, 0x58, 0x78});
		parse_request();
		assert_slave(0);
	});

	run_test("Parse a raw Modbus RTU request with invalid CRC", [](){
		set_mode("rtu");
		set_request({0x01, 0x06, 0xab, 0xcd, 0x01, 0x23, 0xfa, 0xce});
		parse_request();
		assert_slave(0);
	});

	run_test("Parse a raw Modbus RTU response (exception)", [](){
		build_request({1, 1, 0, 1});
		set_response({1, 0x81, 1, 0x81, 0x90});
		parse_response();
		dump_master();
		assert_master(1);
	});

	run_test("Parse a raw Modbus RTU response (exception) with invalid CRC", [](){
		build_request({1, 1, 0, 1});
		set_response({1, 0x81, 1, 0xff, 0xff});
		parse_response();
		dump_master();
		assert_master(0);
	});

	run_test("Parse empty RTU request frame", [](){
		set_mode("rtu");
		set_request({});
		parse_request();
		assert_slave(0);
	});

	run_test("Parse empty RTU response frame", [](){
		set_mode("rtu");
		set_response({});
		parse_response();
		assert_master(0);
	});

	run_test("Broadcast frame with invalid CRC", [](){
		set_mode("rtu");
		set_request({0, 1, 0, 0, 0, 4, 0xff, 0xff});
		parse_request();
		dump_slave();
		assert_slave(0);
		assert_slave_ex(MODBUS_EXCEP_NONE);
	});

	run_test("Cause slave exception in request 01", [](){
		set_mode("rtu");
		set_request({1, 1, 0, 0, 0, 0, 0x3c, 0x0a});
		parse_request();
		dump_slave();
		assert_slave(1);
		assert_slave_ex(MODBUS_EXCEP_ILLEGAL_VALUE);
	});

	run_test("Slave exception to broadcast request 01", [](){
		set_mode("rtu");
		set_request({0, 1, 0, 0, 0, 0, 0x3d, 0xdb});
		parse_request();
		dump_slave();
		dump_response();
		assert_slave(1);
		assert_slave_ex(MODBUS_EXCEP_NONE);

		// todo assert response length == 0
	});

	run_test("Check response to broadcast read request", [](){
		set_mode("rtu");
		build_request({0, 1, 0, 4});
		parse_request();
		dump_slave();
		dump_response();
		assert_slave(1);
		assert_slave_ex(MODBUS_EXCEP_NONE);

		// todo assert response length == 0
	});
}

void modbus_tcp_tests()
{
	run_test("Parse empty TCP request frame", [](){
		set_mode("tcp");
		set_request({});
		parse_request();
		assert_slave(0);
	});

	run_test("Parse empty TCP response frame", [](){
		set_mode("tcp");
		set_response({});
		parse_response();
		assert_master(0);
	});
}

void test_main()
{
	modbus_pdu_tests();
	modbus_rtu_tests();
	modbus_tcp_tests();

	last_register_tests();
	max_read_tests();
}